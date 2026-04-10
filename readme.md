# 🌌 Gestión de Procesos en Linux: Bifurcación y Concurrencia en C (Star Wars Edition)

¡Bienvenido! Este repositorio es un proyecto educativo diseñado para entender empíricamente cómo el núcleo (*kernel*) de Linux gestiona la creación de procesos, la memoria virtual y la sincronización, utilizando el lenguaje C y la API estándar POSIX.

A través de una narrativa basada en el universo de *Star Wars*, este tutorial te guiará **paso a paso**, desde la instalación del entorno hasta la compilación y ejecución, explicando el *por qué* y el *para qué* de cada línea de código.

---

## 🛠️ Fase 1: Instalación y Entorno (Windows / Ubuntu)

Para compilar código C que invoca primitivas POSIX como `fork()`, necesitas un entorno Linux. Si usas Windows, la forma moderna y profesional es usar **WSL (Windows Subsystem for Linux)**.

### Paso 1: Instalar Ubuntu
Abre **PowerShell como Administrador** en tu Windows y ejecuta:
```bash
wsl --install -d Ubuntu
¿Por qué? Windows no entiende la función fork() nativamente. Este comando descarga el Kernel real de Linux y el sistema de archivos de Ubuntu dentro de tu Windows, permitiéndote ejecutar herramientas de bajo nivel.

(Nota: Reinicia tu equipo si te lo solicita y configura tu usuario/contraseña).

Paso 2: Aprovisionar Herramientas
Una vez dentro de la terminal de Ubuntu, actualiza los repositorios e instala las herramientas de compilación:

Bash
sudo apt update
sudo apt install gcc make -y
¿Para qué? gcc es la Colección de Compiladores de GNU, el traductor que convertirá tu texto en C a un binario que el procesador entienda. make es una herramienta de orquestación que automatiza la compilación para no escribir comandos largos manualmente.

Paso 3: Clonar este Repositorio
Bash
git clone [https://github.com/mitchelfalcon/Vader_fork_uvm/](https://github.com/mitchelfalcon/Vader_fork_uvm/)
cd Vader_fork_uvm
👨‍💻 Fase 2: Creación de los Archivos de Código
Si no clonaste el repo y quieres crear los archivos tú mismo, haz lo siguiente:

1. El Proceso Básico (vader_fork.c)
Escribe nano vader_fork.c, pega el código y guarda (Ctrl+O, Enter, Ctrl+X):

C
#include 
#include 
#include 
#include 
#include 

int main() {
    pid_t pid; 

    printf("[SYSTEM] Process starting... PID: %d\n", getpid());
    pid = fork(); // ¡LA CLONACIÓN OCURRE AQUÍ!

    if (pid < 0) {
        fprintf(stderr, "[ERROR] Fork failed.\n");
        exit(1);
    } 
    else if (pid == 0) {
        // Ejecutado SOLO por el Hijo (Luke)
        printf(" -> [CHILD] My PID is %d.\n", getpid());
        sleep(2); // Simula trabajo asíncrono
        printf("\n -> [CHILD] (Luke): \"You killed my father!\"\n");
        exit(0); // Notifica su muerte
    } 
    else {
        // Ejecutado SOLO por el Padre (Vader)
        int status; 
        printf(" -> [PARENT] My PID is %d. Child PID is %d.\n", getpid(), pid);
        
        wait(&status); // SINCRONIZACIÓN: Evita Zombies
        
        printf("\n -> [PARENT] (Darth Vader): \"No, **I AM YOUR FATHER**.\"\n");
    }
    return 0;
}
2. El Crecimiento Exponencial (vader_loop.c)
Escribe nano vader_loop.c, pega y guarda:

C
#include 
#include 
#include 
#include 
#include 

int main(int argc, char *argv[]) {
    printf("[KAMINO FACILITY] Initiating Clone Army Production...\n");
    
    // Bucle de clonación exponencial: 2^4 = 16 procesos
    for (int i = 1; i <= 4; i++) {
        fork(); 
        printf("Phase %d: Clone reporting! My PID = %d\n", i, (int) getpid());
    }

    sleep(1);
    // Limpieza masiva para no dejar huérfanos/zombies
    while (wait(NULL) > 0); 
    return 0;
}
3. El Orquestador (Makefile)
Escribe nano Makefile, pega y guarda. (Asegúrate de que la línea de gcc comience con un TAB, no con espacios):

Makefile
TARGETS=vader_fork vader_loop
CC_C = gcc
CFLAGS = -Wall -g -std=c99 -Werror

all: clean $(TARGETS)

$(TARGETS):
	$(CC_C) $(CFLAGS) $@.c -o $@

clean:
	rm -f $(TARGETS)
¿Por qué un Makefile? Compilar con gcc archivo.c -o archivo está bien, pero en proyectos serios, el Makefile aplica reglas estrictas (-Wall muestra todas las advertencias, -Werror las convierte en errores bloqueantes), garantizando que tu código es seguro antes de ejecutarse.

🚀 Fase 3: Compilación y Ejecución (El Análisis)
Compilación Automatizada
En tu terminal, simplemente escribe:

Bash
make
El sistema leerá el Makefile, borrará binarios antiguos y compilará limpiamente vader_fork y vader_loop.

Ejecutar Ejercicio 1 (La Anatomía)
Bash
./vader_fork
¿Qué sucede y por qué?
Al invocar fork(), la memoria se divide. El sistema operativo devuelve 0 al proceso hijo, obligándolo a entrar al bloque else if. Al proceso padre le devuelve un número (ej. 4091), obligándolo a entrar al bloque else.  El padre ejecuta wait(&status), que lo congela. Esto es crítico: si el padre no espera y termina, el hijo queda como Huérfano. Si el hijo termina y el padre nunca lee su muerte, se vuelve un Zombie (ocupa espacio en el SO sin hacer nada).

Ejecutar Ejercicio 2 (La Bomba Lógica)
Bash
./vader_loop
¿Qué sucede y por qué?
Verás tu consola inundarse de mensajes. Un bucle for de 4 iteraciones no crea 4 procesos. Al estar el fork() dentro, el primer proceso se clona (2), luego esos 2 se clonan (4), luego 8, y finalmente 16 procesos concurrentes. Esto se conoce matemáticamente como 2 
n
 . Hemos añadido un while(wait(NULL) > 0); al final para obligar al sistema a limpiar masivamente todos los clones generados, protegiendo tu procesador de un desbordamiento.

Creado con ❤️ para que estudiantes de programación aprendan.

Universidad del Valle de México | Sistemas Operativos > Actividad 2. Ejercicios | Mtra. Judith Jiménez García
