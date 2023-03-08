# LPC845 - Drivers C++
Proyecto creacion de un sistema embebido utilizando base un LPC 845.
<br>
creacion de drivers para un LPC 845.

<p>
  <img src="https://www.nxp.com/assets/images/en/dev-board-image/LPC845-BRK-1.JPG"
  </p>
  <br>
  
### 💻 Lenguajes y herramientas 💻👨
<p>
  <img src="https://cdn-icons-png.flaticon.com/512/6132/6132222.png" width="25" height="25"/>
  C++ Para aprovechar el paradigma de objetos
  </p>
  
:computer: IDE : MCUExpresso v11.6.8255
<br>
### Drivers
<br>

- UART.
- I2C. _Aun en proceso_.
- GPIO.
- Systick.
- SPI _Problemas con la linea Clock_.
- PWM.
- MRT _Con asignacion de funciones utilizando sobrecarga de operadores y puntero a funcion_.
<br>

### Extras

<br>

- Objeto para guardar y gestionar los Pines-Puertos de la forma que los registros lo solicita.
- Creacion de buffers particulares para el protocolo de comunicacion
- Configuracion de metodos para la reasignacion de funciones.

<br>

### Cosas aprendidas y retos

<br>

La utilizacion del entorno MCUExpresso en si fue un reto por sus particulares asi como herramientras que probe para la observacion de los registros en tiempo de ejecucion _Realizando una pausa en la misma_

<br>

Aplicacion del paradigma de orientado a eventos utilizando como herramienta el paradigma orientado a objetos que provee el C++.

<br>

Nuevas formas de sintaxis propias del lenguaje para le creacion por ejemplo de Vectores de puntero a funciones.

<br>

Lectura del Datasheel asociado al microcontrolador.
<br>

Lectura e interpretacion de errores sin el soporte de un sistema operativo que ayude a su interpretacion.
### Pines 🔍 
<br>
<p>
  <img src="https://www.nxp.com/assets/images/en/block-diagrams/LPC845-BRK-BD2.png"/>
  </p>
