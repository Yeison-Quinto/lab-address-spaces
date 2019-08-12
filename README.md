# The Abstraction: Address Spaces #

[![Developed by @santiago-b9826](https://img.shields.io/badge/developed%20by-%40SantiagoBedoya-blue.svg  "Santiago Bedoya")](https://github.com/santiago-b9826)   [![Developed by @linamariaum](https://img.shields.io/badge/developed%20by-%40linamariaum-ff69b4.svg  "Lina María Uribe")](https://github.com/linamariaum)


En esta tarea aprenderemos sobre unas herramientas útiles para examinar el uso de memoria virtual de sistemas basados en Linux. 
Esto solo será una breve pista de lo que es posible; será necesario sumergirse más profundamente para convertirte verdaderamente 
en un experto (¡Como siempre!).

## Antes de empezar ##

Para responder a las preguntas lea y reflexione sobre el capítulo [The Abstraction: Address Spaces]( http://pages.cs.wisc.edu/~remzi/OSTEP/vm-intro.pdf) pues de este fue del que se sacaron las preguntas. Adicionalmente entienda y ejecute el código asociado a dicho capítulo el cual se encuentra en el siguiente [enlace](https://github.com/remzi-arpacidusseau/ostep-code/tree/master/vm-intro). 

Adicionalmente, donde crea que sea necesario haga uso de los conceptos sobre procesos aprendidos en el laboratorio anterior.

## Preguntas ##

1. La primera herramienta que analizaremos es una herramienta muy simple, ```free```. Primero, abra una terminal de Linux y 
teclee ```man free```, lea su manual entero; es breve, no se preocupe! ¿Para qué sirve este comando?. **Nota**: Puede apoyarse en 
material web para entender la herramienta mediante ejemplos.
    > El comando ```free```, muestra la cantidad de memoria libre y usada en el sistema. Muestra la cantidad total de memoria física y de intercambio libre y usada en el sistema, así como los búferes y cachés utilizados por el kernel.
    >
    >De las opciones más utiles, esta la posibilidad de mostrar la cantidad de memoria en diferentes unidades (Muestra en Kilobytes por defecto). ```-b or --bytes``` , ```-k or --kilo```, ```-m or --mega```, ```-g or --giga```, ```--tera```. Mostrar estadísticas detalladas de baja y alta memoria ```-l, --lohi```.

2. Ahora, ejecute ```free``` usando algunos argumentos que podrían ser útiles (por ejemplo, ```-m```, para mostrar 
la cantidad total de memoria en megabytes). ¿Cuánta memoria hay en su sistema?, ¿Cuánta está libre? 
¿Son estos valores los que usted esperaba?
    > En el sistema hay ```7924 megas``` correspondientes a ```7 gigas```. De las cuales ```244 megas``` se encuentran libres para la memoria y ```8012 megas``` para el espacio de intercambio.
    > La columna ```free``` hace referencia a memoria no utilizada; mientras que la columna ```available``` se refiere a la estimación de cuánta memoria está disponible para iniciar nuevas aplicaciones, sin intercambiar. A diferencia de los datos proporcionados por la memoria caché o los campos free, este campo tiene en cuenta la memoria caché de la página y también que no se recuperarán todos los bloques de memoria reclamables debido a los elementos en uso.
    ![Salida de la consola al ejecutar el comando: free -m](https://raw.githubusercontent.com/santiago-b9826/lab-address-spaces/master/assets/2.png)

3. A continuación, cree un pequeño programa que use cierta cantidad de memoria, llamado ```memory-user.c```. 
Este programa debe tomar un argumento por linea de comandos: el número de megabytes de memoria que usted usará. 
Cuando lo ejecute, el programa debe separar memoria para un arreglo (vector) y recorrer el arreglo, 
accediendo consecutivamente a cada entrada (por ejemplo, escribiendo un valor inicial a cada posición). El programa deberá hacer esto indefinidamente o, 
por lo menos, por una cierta cantidad de tiempo especificada también por línea de comandos.
    > Para compilar el programa ```memory-user.c```, ejecutar el comando ```gcc memory-user.c -o memory-user.out -Wall -lm``` en la ubicación el archivo C.
    >
    > Este programa toma argumentos por línea de comandos, el primero es el número de megabytes de memoria que se usará; y el segundo la cantidad de tiempo que el programa accederá y recorrerá el arreglo, este último argumento no es obligatorio, en caso de no ser ingresado, el programa accederá y recorrerá el arreglo indefinidamente.
    > Ejemplos de ejecución del programa:
    >
    >```./memory-user.out 5```
    >
    >```./memory-user.out 4 1```

4. Ahora, mientras corra su programa ```memory-user.c```, ejecute la herramienta ```free``` (en una terminal diferente, 
pero en la misma máquina). ¿Cómo cambia el uso total de memoria cuando su programa está corriendo?,
¿Qué pasa cuando se finaliza el programa memory-user (comando kill)?, ¿coinciden los valores con lo que usted esperaba? 
Intente esto para diferentes cantidades de uso de memoria. ¿Qué pasa cuando usted usa cantidades de memoria realmente grandes?
    > ```FALTA``` Intenté con 5 10 20 200 200, y este fue el resultado
    ![Salida de la consola al ejecutar el comando: free -m](https://raw.githubusercontent.com/santiago-b9826/lab-address-spaces/master/assets/4.png)

5. Ahora veremos una herramienta más conocida como ```pmap```. Invierta algo de tiempo para leer el manual de ```pmap``` 
en detalle. ¿Cuál es la diferencia de ```pmap``` con ```free```?
    > El comando ```pmap``` informa el mapa de memoria de un proceso o procesos.
    La diferencia entre ```pmap``` y ```free``` es que ```pmap``` muestra el mapeo de un **proceso** (o varios procesos) en la memoria (indicando direcciones virtuales asignadas, tamaño, permisos, dispositivos, entre otros). Mientras que ```free``` nos muestra de manera general el uso de la memoria física y el espacio swap del **sistema** (Indicando total, libre, compartida, disponible, entre otros).

6. Para usar pmap, usted tiene que conocer el identificador de proceso (PID) del proceso en el que usted está interesado. 
Por lo tanto, primero ejecute ```ps auxw``` para ver una lista con todos lo procesos; entonces, 
seleccione alguno de su interés tal como un browser. Usted también puede usar su programa memory-user en este caso 
(de hecho, usted puede hacer que ese programa llame a ```getpid()``` para imprimir su PID para su conveniencia).

7. Ahora ejecute ```pmap``` en alguno de estos procesos usando varias flags (como ```-X```) para revelar más detalles 
acerca del proceso. ¿Qué puede ver? ¿Cuántas entidades diferentes conforman un espacio de direcciones moderno, a diferencia de 
nuestra simple concepción de code/stack/heap?

8. Finalmente, ejecute ```pmap``` para su programa memory-user, con diferentes cantidades de memoria usada. ¿Qué puede ver en este caso?  ¿La salida de ```pmap``` es siempre la que usted espera?

## Referencias ##

1. http://u.cs.biu.ac.il/~linraz/os/OS3.pdf
2. https://www.ostechnix.com/run-command-specific-time-linux/
3. http://u.cs.biu.ac.il/~linraz/os/OS4.pdf
4. http://u.cs.biu.ac.il/~linraz/os/OS5.pdf
