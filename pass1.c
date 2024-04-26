#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void display();

int main() {
    char opcode[10], operand[10], label[10], code[10], mnemonic[10];
    int locctr, start, length;

    FILE *fp1, *fp2, *fp3, *fp4;

    fp1 = fopen("input.txt", "r");
    fp2 = fopen("optab.txt", "r");
    fp3 = fopen("symtab.txt", "w");
    fp4 = fopen("out.txt", "w");

    if (fp1 == NULL || fp2 == NULL || fp3 == NULL || fp4 == NULL) {
        printf("Error opening files.\n");
        return 1;
    }

    fscanf(fp1, "%s %s %s", label, opcode, operand);

    if(strcmp(opcode, "START") == 0) {
        start = atoi(operand);
        locctr = start;
        fprintf(fp4, "\t%s\t%s\t%s\n", label, opcode, operand);
        fscanf(fp1, "%s %s %s", label, opcode, operand);
    }
    else {
        locctr = 0;
    }

    while(strcmp(opcode, "END") != 0 && !feof(fp1)) {
        fprintf(fp4, "%d\t", locctr);

        if(strcmp(label, "**") != 0) {
            fprintf(fp3, "%s\t%d\n", label, locctr);
        }

        rewind(fp2); // Reset file position indicator to the beginning of fp2
        fscanf(fp2, "%s %s", code, mnemonic);

        while(strcmp(code, "END") != 0 && !feof(fp2)) {
            if(strcmp(opcode, code) == 0) {
                locctr += 3;
                break;
            }
            fscanf(fp2, "%s %s", code, mnemonic);
        }

        if(strcmp(opcode, "WORD") == 0) {
            locctr += 3;
        }
        else if(strcmp(opcode, "RESW") == 0) {
            locctr += (3 * atoi(operand));
        }
        else if(strcmp(opcode, "RESB") == 0) {
            locctr += atoi(operand);
        }
        else if(strcmp(opcode, "BYTE") == 0) {
          
            if(operand[0] == 'C') {
                locctr += strlen(operand) - 3;
            }
            else if(operand[0] == 'X') {
                locctr += (strlen(operand) - 3) / 2;
            }
        }
        else if(strcmp(opcode, "DC") == 0) {
           
            locctr += 4; 
        }
        else if(strcmp(opcode, "DS") == 0) {
            locctr += atoi(operand);
        }

        fprintf(fp4, "%s\t%s\t%s\t\n", label, opcode, operand);
        fscanf(fp1, "%s %s %s", label, opcode, operand);
    }

    fprintf(fp4, "%d\t%s\t%s\t%s\n", locctr, label, opcode, operand);

    length = locctr - start;

    printf("The length of the code: %d\n", length);

    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
    
    display();
    return 0;
}

void display() {

    char str;
    FILE *fp2, *fp3;   


    //2. Output Table
    printf("\n\nThe contents of Output Table :\n\n");
    fp2 = fopen("out.txt", "r");
    str = fgetc(fp2);
    while (str != EOF) {
        printf("%c", str);
        str = fgetc(fp2);
    }
    fclose(fp2);

    // 3. Symtable
    printf("\n\nThe contents of Symbol Table :\n\n");
    fp3 = fopen("symtab.txt", "r");
    str = fgetc(fp3);
    while (str != EOF) {
        printf("%c", str);
        str = fgetc(fp3);
    }
    fclose(fp3);
}
