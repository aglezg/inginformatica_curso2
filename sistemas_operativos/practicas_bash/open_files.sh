#!/bin/bash

# ULL - Grado en Ingeniería Informática
# Segundo Curso - Asignatura: Sistemas Operativos
# Práctica de BASH: Ficheros abiertos por usuarios
# Autor: Adrián Glez Galván - alu0101321219@ull.edu.es (Grupo Tarde)

##### Constantes

TITLE="Listado de usuarios con archivos abiertos para '$HOSTNAME'"
PROGNAME=$(basename $0)
TEMP_FILE=$(tempfile --prefix="tmp" --suffix=".open_files.$$")
TEMP_FILE2=$(tempfile --prefix="tmp" --suffix=".open_files.$$")

#### Variables no constantes

pattern=
offline=0
one_user=0
users_list=$(who | sort | uniq | cut -d ' ' -f1)

##### Estilos

TEXT_BOLD=$(tput bold)
TEXT_GREEN=$(tput setaf 2)
TEXT_RESET=$(tput sgr0)
TEXT_ULINE=$(tput sgr 0 1)

#### Comprobación de lsof está instalado
test $(type -P lsof)
if [ "$?" != "0" ]; then
  echo "${PROGNAME} : El comando 'lsof' no se encuentra instalado."
  rm $TEMP_FILE $TEMP_FILE2
  exit 2
fi

##### Funciones

print_list()
{
   # Columnas 
  echo -e "${TEXT_ULINE}USUARIO\t\t\tNºFicherosAbiertos\t\tUID\t\t\t'PID'ProcesoMasAntiguo$TEXT_RESET"
  # Para cada usuario de la lista: nombre - número de ficheros abiertos - UID - PID del proceso más antiguo
  for user in $1; do
    number_of_files=$(lsof -u $user | tail -n +2 | grep "$pattern$" | wc -l)
    uid=$(id -u $user)
    pid=$(ps h -U $user -u $user -oetime,pid | sort -k 1 -r | head -n 1 | tr -s ' ' ' ' | cut -d ' ' -f3)
    echo -e "$user \t\t\t$number_of_files\t\t\t\t$uid\t\t\t$pid"
    echo
  done
}

open_files()
{
    if (( ! $offline )); then
      print_list $users_list  # Imprimimos lista de usuarios
    fi
}

open_files_offline()
{
  if (( $offline )); then
    # Creamos una segunda lista de usuarios  
    lsof -F | grep -s '^L' | sort | uniq | cut -d 'L' -f2 > $TEMP_FILE
    # Para cada usuario de la lista: nombre - número de ficheros abiertos - UID - PID del proceso más antiguo
    for user in $users_list; do
      grep -vx $user $TEMP_FILE > $TEMP_FILE2
      cat $TEMP_FILE2 > $TEMP_FILE
    done
    # Imprimimos la lista
    print_list "$(cat $TEMP_FILE)"

  fi
}

usage()
{
   echo "usage: ./open_files.sh [-f 'pattern'] [-o] [-u 'user'] [-h]"
}

error_exit()
{
    echo "${PROGNAME} : ${1:-"Error desconocido"}" 1>&2
    rm $TEMP_FILE $TEMP_FILE2
    exit 1
}

##### Programa principal

# Lectura de opciones
while [ "$1" != "" ]; do
  case $1 in

    -h | --help )
      usage
      exit 0
    ;;

    -f | --filter)
    shift
    pattern=$1
    ;;

    -o | --off_line)
    offline=1
    ;;

    -u | --user)
      shift
      users_list=$1
      one_user=1
      # Comprobamos que el usuario exista
      test $(lsof -F | grep -s '^L' | sort | uniq | cut -d 'L' -f2 | grep -w $users_list$)
      if [ "$?" != "0" ]; then
        error_exit " El usuario introducido no existe."
      fi
    ;;

    * )
    usage
    error_exit "Opción introducida desconocida."

  esac
  shift
done

# Comprobación de que no se usan los parámetros [-u] y [-o] a la vez
if [[ "$one_user" = "1" && "$offline" = "1" ]]; then
  error_exit "La única opción permitida al especificar un usuario es [-f]."
fi

# Main
main(){

cat << _EOF_

$TEXT_BOLD$TITLE$TEXT_RESET

$(open_files)$(open_files_offline)

_EOF_

}

main
rm $TEMP_FILE $TEMP_FILE2