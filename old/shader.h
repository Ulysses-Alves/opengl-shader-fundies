#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>

typedef struct{
    unsigned int ID;
}Shader;

Shader createShader(const char* vertexPath, const char* fragmentPath){
    char vertxCode[] = "";
    char fragmentCode[] = "";
    FILE* vShaderFile;
    FILE* fShaderFile;
    
    vShaderFile = fopen(vertexPath,"r");
    
    if(!vShaderFile){
        perror("Error opening file.");
        fclose(vShaderFile);
        exit(EXIT_FAILURE);
    }

    fShaderFile = fopen(fragmentPath, "r");

    if(!fShaderFile){
        perror("Error opening file.");
        fclose(fShaderFile);
        exit(EXIT_FAILURE);
    }

    char* buffer = nullptr;



}
void useShader(Shader* shader);
void setShaderBool(Shader* shader, const char* name, bool value);
void setShaderInt(Shader* shader, const char* name, int value);
void setShaderFloat(Shader* shader, const char* name, float value);

#endif