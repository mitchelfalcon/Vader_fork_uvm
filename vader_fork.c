#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid; // Variable para almacenar el ID del proceso

    // Fase 1: Punto de bifurcación
    printf("[SYSTEM] Process starting... PID: %d\n", getpid());
    printf("[SYSTEM] Attempting to create a new process...\n\n");

    // Se invoca la llamada al sistema fork()
    pid = fork();

    // Fase 2: Diagnóstico y desviación del flujo
    if (pid < 0) {
        // Estado: [Distractor - Factualmente Incorrecta] Error grave del sistema
        fprintf(stderr, "[ERROR] Fork failed. The galaxy is in chaos.\n");
        exit(1);
    } 
    else if (pid == 0) {
        // Estado: [Correcta] Bloque ejecutado ÚNICAMENTE por el proceso HIJO
        // Se aplica la Heurística H2 (Prioridad al Concepto Central): 
        // Aunque el usuario solicitó la cita, la función técnica aquí es reportar su identidad.
        
        printf(" -> [CHILD] My PID is %d. I think I am a separate process...\n", getpid());
        printf(" -> [CHILD] Wait, I feel a disturbance in the Force.\n");
        
        sleep(2); // Simulación de procesamiento concurrente
        
        printf("\n -> [CHILD] (Luke): \"You killed my father!\"\n\n");
        
        printf(" -> [CHILD] Finishing execution.\n");
        exit(0); // El hijo termina voluntariamente
    } 
    else {
        // Estado: [Correcta] Bloque ejecutado ÚNICAMENTE por el proceso PADRE
        // La variable 'pid' contiene el PID del hijo (ej. > 0).
        
        int status; // Variable para recibir el estado del hijo
        
        printf(" -> [PARENT] My PID is %d. I have created a child process with PID %d.\n", getpid(), pid);
        printf(" -> [PARENT] Waiting for my child to realize the truth...\n");
        
        // Fase 3: Sincronización (Crucial para evitar procesos Zombies)
        // El padre se bloquea hasta que el hijo llama a exit().
        wait(&status); 
        
        // Fase 4: Entrega de la cita solicitada
        printf("\n -> [PARENT] (Darth Vader): \"No, **I AM YOUR FATHER**.\"\n\n");
        
        printf(" -> [PARENT] Finishing execution.\n");
    }

    return 0;
}