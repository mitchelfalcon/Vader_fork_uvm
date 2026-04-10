5. Guía y Tutorial Paso a Paso (README.md para GitHub)

Copia todo el contenido a partir de este punto y pégalo directamente en el archivo README.md de tu repositorio. Está diseñado en formato Markdown nativo.

🌌 Gestión de Procesos en Linux: Bifurcación y Concurrencia en C (Star Wars Edition)

¡Bienvenido! Este repositorio es un proyecto educativo diseñado para entender empíricamente cómo el núcleo (kernel) de Linux gestiona la creación de procesos, la memoria virtual y la sincronización, utilizando el lenguaje C y la API estándar POSIX.

A través de una narrativa basada en el universo de Star Wars, este tutorial te guiará paso a paso para comprender qué sucede realmente en tu procesador cuando invocas las poderosas llamadas al sistema fork() y wait().

🛠️ Requisitos Previos e Instalación

Para ejecutar estos experimentos, necesitas un entorno basado en UNIX/Linux. Si eres usuario de Windows, puedes instalar Ubuntu nativamente a través de WSL (Windows Subsystem for Linux). Sigue estos pasos cuidadosamente:

Instala Ubuntu (Solo para usuarios de Windows):
Abre PowerShell como Administrador y ejecuta el siguiente comando:

wsl --install -d Ubuntu


(Una vez que termine, reinicia tu equipo si te lo solicita y configura tu nuevo usuario y contraseña de UNIX en la terminal que se abrirá).

Clona el repositorio y navega al directorio (en tu terminal de Ubuntu):

git clone [https://github.com/mitchelfalcon/Vader_fork_uvm/](https://github.com/mitchelfalcon/Vader_fork_uvm/)
cd Vader_fork_uvm


Instala el compilador y herramientas de orquestación (gcc y make):
Para poder traducir el código en C a un binario ejecutable, actualiza tu sistema operativo e instala las herramientas necesarias ejecutando:

sudo apt update
sudo apt install gcc make -y


Compila los programas utilizando el orquestador automático:

make


👨‍👦 Tutorial 1: Entendiendo vader_fork.c (Bifurcación Básica)

Ejecución: ./vader_fork

¿De qué se trata?

En los sistemas Linux, los procesos no nacen de la nada; se clonan. Cuando un programa invoca la función fork(), el sistema operativo congela el proceso original (el Padre / Darth Vader) y crea una copia exacta en la memoria RAM (el Hijo / Luke Skywalker). A partir de la línea donde se llamó a fork(), ambos programas comienzan a ejecutarse al mismo tiempo (concurrencia).

Paso a Paso en el Código:

La Bifurcación: La variable pid_t pid = fork(); es el momento crítico. El sistema operativo clona el proceso.

Desviación del Flujo (if / else): Como padre e hijo son clones idénticos, ¿cómo saben qué hacer? ¡Por el valor de retorno de fork()!

En el proceso Hijo: fork() devuelve 0. Entra en el bloque else if (pid == 0) y ejecuta las líneas de Luke. Luego, llama a exit(0) para terminar su ciclo vital.

En el proceso Padre: fork() devuelve el PID (Identificador de Proceso) del hijo (un número > 0). Entra en el bloque else y ejecuta las líneas de Vader.

La Sincronización (wait): En el bloque del Padre, notarás la instrucción wait(&status);. Esto es fundamental. Si el padre termina antes que el hijo, el hijo queda "huérfano". Si el hijo termina y el padre no lee su estado, el hijo se vuelve un "proceso zombie" (muerto, pero ocupando espacio en la tabla del sistema). wait() obliga al padre a hacer una pausa hasta que el hijo se extinga por completo.

🧬 Tutorial 2: Entendiendo vader_loop.c (La Bomba Lógica / El Ejército Clon)

Ejecución: ./vader_loop

¿De qué se trata?

Este programa responde a la pregunta técnica: ¿Qué pasa si ponemos un fork() dentro de un bucle for iterativo? La intuición nos diría que un bucle de 4 iteraciones creará 4 procesos. La realidad es exponencial.

Paso a Paso en el Código:

Observa este fragmento letal:

for (int i = 1; i <= 4; i++) {
    fork(); 
}


Iteración 1: El proceso Padre original crea 1 Hijo. (Total: 2 procesos activos).

Iteración 2: Tanto el Padre como el Hijo 1 están activos y ambos alcanzan el fork(). Cada uno crea 1 hijo. (Total: 4 procesos activos).

Iteración 3: Los 4 procesos invocan fork(). (Total: 8 procesos activos).

Iteración 4: Los 8 procesos invocan fork(). (Total: 16 procesos activos generados casi a la velocidad de la luz).

La Matemática: La cantidad de procesos creados se rige por la fórmula $2^n$, donde $n$ es el número de iteraciones.

La Solución de Sincronización Masiva:

Para evitar colapsar el sistema operativo dejando 15 clones huérfanos o en estado zombie, utilizamos una limpieza sistemática al final del código:

while (wait(NULL) > 0);


Esta línea mágica le ordena a cada proceso (sea el Prime Clone original o los sub-clones) que espere a la extinción de absolutamente todos sus descendientes directos antes de invocar su propio return 0;. Garantiza una destrucción en cascada limpia de la memoria, salvaguardando la integridad del hardware.

Creado con ❤️ para que estudiantes de programación aprendan.

Universidad del Valle de México | Sistemas Operativos > Actividad 2. Ejercicios | Mtra. Judith Jiménez García