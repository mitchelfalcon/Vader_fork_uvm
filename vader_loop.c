#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    printf("[KAMINO FACILITY] Initiating Clone Army Production...\n");
    printf("[KAMINO FACILITY] Original Prime Clone Jango Fett (PID: %d) ready.\n\n", getpid());

    // Bucle de clonación exponencial: 2^4 = 16 procesos totales en la jerarquía
    for (int i = 1; i <= 4; i++) {
        fork(); // La llamada que duplica el proceso actual en cada iteración
        
        // Cada clon (y el padre) reportan su existencia concurrente
        printf("Phase %d: Clone reporting for duty! My PID = %d\n", i, (int) getpid());
    }

    // Retardo para permitir que el planificador (scheduler) de Linux ejecute a todos los clones
    sleep(1);
    
    // Reporte final antes de terminar
    printf("--> [DEPLOYMENT] Unit (PID: %d) marching to the Republic ships.\n", (int) getpid());

    // Asegurar que no queden procesos zombies. 
    // Los procesos esperan a cualquier descendiente directo antes de terminar.
    while (wait(NULL) > 0); 

    return 0;
}
