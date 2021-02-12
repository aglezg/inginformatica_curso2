#!/bin/bash

# Practica de Sistemas Operativos!
# sysinfo - Un script que informa del estado del sistema

# Autor:
# Adrián Glez Galvan - alu0101321219@ull.edu.es (Grupo Tarde)

##### Constantes

TITLE="Información del sistema para $HOSTNAME"

RIGHT_NOW=$(date +"%x %r%Z")
TIME_STAMP="Actualizada el $RIGHT_NOW por $USER"
interactive=
filename=~/sysinfo.txt

var_procs=0

##### Estilos

TEXT_BOLD=$(tput bold)
TEXT_GREEN=$(tput setaf 2)
TEXT_RESET=$(tput sgr0)
TEXT_ULINE=$(tput sgr 0 1)

##### Funciones

system_info()
{
   echo "${TEXT_ULINE}Versión del sistema${TEXT_RESET}"
   echo
   uname -a
}


show_uptime()
{
   echo "${TEXT_ULINE}Tiempo de encendido del sistema${TEXT_RESET}"
   echo
   uptime
}


drive_space(){
  echo "${TEXT_ULINE}Espacio en el sistema de archivos${TEXT_RESET}"
  echo
  df
}


home_space()
{
  if [ "$USER" = "root" ] # sólo el superusuario puede obtener esta información
  then
    echo "${TEXT_ULINE}Espacio en home por usuario${TEXT_RESET}"
    echo
    echo "Bytes Directorio"
    du -s /home/* | sort -nr
  fi
}

usage()
{
   echo "usage: sysinfo [-f file ] [-i] [-procs] [-h]"
}

num_of_processes(){

  if (( $var_procs )); then
    lista_procesos=$(ps h ax -ouser | sort | uniq) #lista de los usuarios ejecutando procesos

    echo "${TEXT_ULINE}Número de procesos abiertos${TEXT_RESET}"
    echo
    echo -e "${TEXT_UNLINE}USUARIO\t\t\tNºProcesos\t\tTiempoDelProcesoMasEjecutado\n${TEXT_RESET}"

    for usuario in $lista_procesos; do
      contador=$( ps h -u $usuario | wc -l) # numero de procesos de cada usuario
      etime=$( ps h -u $usuario -o etimes | sort -n | uniq | tail -n 1) # Etime del proceso mas ejecutado de cada usuario
      echo -e "$usuario\t\t\t$contador\t\t\t$etime"
      echo
    done
  fi


}

##### Programa principal

# Procesar la línea de comandos del script para leer las opciones
while [ "$1" != "" ]; do
  case $1 in
    -f | --file )
      shift
        filename=$1
    ;;

    -i | --interactive )
      interactive=1
    ;;

    -h | --help )
      usage
      exit
    ;;

    -procs )
    var_procs=1
    ;;

    * )
    usage
    exit 1

  esac
  shift
done

write_page()

{

cat << _EOF_

$TEXT_BOLD$TITLE$TEXT_RESET

$(system_info)


$(show_uptime)


$(drive_space)


$(home_space)

$(num_of_processes)

$TEXT_GREEN$TIME_STAMP$TEXT_RESET

_EOF_

}

# Generar el informe del sistema y guardarlo en el archivo indicado

# en $filename

write_page > $filename
