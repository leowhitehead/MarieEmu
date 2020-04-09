#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef struct cpuState {
    uint16_t MEM[0xfff];
    uint16_t AC;
    uint16_t PC : 0xC;

} cpuState;

void initialiseCpu(cpuState* cpu){
    memset(cpu->MEM, 0, 0xfff*sizeof(uint16_t));
    cpu->AC = 0x0;
    cpu->PC = 0x0;
}

void run(cpuState* cpu){
    uint8_t opcode = cpu->MEM[cpu->PC] >> 12;
    uint16_t x = cpu->MEM[cpu->PC] & 0x0fff;
    
    switch(opcode){
        case 0x3: //Add x
            cpu->AC += cpu->MEM[x];
            cpu->PC++;
            break;
        case 0x4: //Subt x
            cpu->AC -= cpu->MEM[x];
            cpu->PC++;
            break;
        case 0xb: //AddI x
            cpu->AC += cpu->MEM[cpu->MEM[x]];
            cpu->PC++;
            break;
        case 0xa: //Clear
            cpu->AC = 0;
            cpu->PC++;
            break;
        case 0x1: //Load x
            cpu->AC = cpu->MEM[x];
            cpu->PC++;
            break;
        case 0x2: //Store x
            cpu->MEM[x] = cpu->AC;
            cpu->PC++;
            break;
        case 0x5: //Input
            scanf("%hx", &cpu->AC);
            cpu->PC++;
            break;
        case 0x6: //Output
            printf("%x\n", cpu->AC);
            cpu->PC++;
            break;
        case 0x9: //Jump x
            cpu->PC = x;
            break;
        case 0x8: //Skipcond x
            printf("%x\n", cpu->AC);
            if(x==0x000){
                if(cpu->AC < 0)
                    cpu->PC+=2;
            } else if(x==0x400){
                if(cpu->AC == 0)
                    cpu->PC+=2;
            } else if(x==0x800){
                if(cpu->AC > 0)
                    cpu->PC+=2;
            }
            break;
        case 0x0: //JnS x
            cpu->MEM[x] = cpu->PC;
            cpu->PC = x;
            break;
        case 0xc: //JumpI x
            cpu->PC = cpu->MEM[x];
            cpu->PC++;
            break;
        case 0xd: //StoreI x
            cpu->MEM[cpu->MEM[x]] = cpu->AC;
            cpu->PC++;
            break;
        case 0xe: //LoadI x
            cpu->AC = cpu->MEM[cpu->MEM[x]];
            cpu->PC++;
            break;
        case 0x7: //Halt
            exit(0);
            break;
        default:
            printf("Illegal instruction: %x\n", cpu->MEM[cpu->PC]);
            exit(1);
    }
}

int main(int argc, char* argv[]){
    cpuState cpu;
    cpuState* cpuPtr = &cpu;
    FILE* f;
    uint8_t buffer[0xfff*2];
    if(argc == 1){
        printf("Usage: ./marie [file]\n");
        exit(1);
    }
    f = fopen(argv[1], "rb");
    if(f)
        fread(buffer, 0xfff*2, 1, f);
    else{
        printf("Error: Could not open file\n");
        exit(1);
    }
    initialiseCpu(cpuPtr);
    int j = 0;
    for(int i = 0; i < 0xfff; i+=2){
        cpuPtr->MEM[j++] = ((uint16_t)buffer[i] << 8) | buffer[i+1];
    }
    for(;;)
        run(cpuPtr);
}
