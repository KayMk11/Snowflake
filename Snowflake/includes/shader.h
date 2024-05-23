#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <fstream>
#include <sstream>
#include "core.h"

namespace Snowflake
{
    class Shader
    {
    protected:
        unsigned int ID;
        std::string name;
    public:

        Shader() {}
        Shader(std::string _name, std::string vertexShaderPath, std::string fragementShaderPath, std::string geometryShaderPath = "") {}
        virtual void use() = 0;
        virtual void setBool(const std::string &name, bool value) const = 0;
        virtual void setInt(const std::string &name, int value) const = 0;
        virtual void setFloat(const std::string &name, float value) const = 0;
        virtual void setVec2(const std::string &name, const glm::vec2 &value) const = 0;
        virtual void setVec2(const std::string &name, float x, float y) const = 0;
        virtual void setVec3(const std::string &name, const glm::vec3 &value) const = 0;
        virtual void setVec3(const std::string &name, float x, float y, float z) const = 0;
        virtual void setVec4(const std::string &name, const glm::vec4 &value) const = 0;
        virtual void setVec4(const std::string &name, float x, float y, float z, float w) const = 0;
        virtual void setMat2(const std::string &name, const glm::mat2 &mat) const = 0;
        virtual void setMat3(const std::string &name, const glm::mat3 &mat) const = 0;
        virtual void setMat4(const std::string &name, const glm::mat4 &mat) const = 0;

        unsigned int getNativeShader() { return ID; }
        std::string getName() { return name; }

    };

    class OpenGLShader : public Shader
    {
        void checkErrors(unsigned int shader, std::string type)
        {
            int success;
            char infoLog[512];
            unsigned int flag;
            if (type == "PROGRAM")
            {
                glGetShaderiv(shader, GL_LINK_STATUS, &success);
                if (!success)
                {
                    glGetShaderInfoLog(shader, 512, NULL, infoLog);
                    std::cout << "ERROR::SHADER::" << type << "::LINK_FAILURE\n"
                            << infoLog << std::endl;
                    std::cout << "------------------------------------------------------------------------" << std::endl;
                };
            }
            else
            {
                glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
                if (!success)
                {
                    glGetShaderInfoLog(shader, 512, NULL, infoLog);
                    std::cout << "ERROR::SHADER::" << type << "::COMPILATION_FAILURE\n"
                            << infoLog << std::endl;
                    std::cout << "------------------------------------------------------------------------" << std::endl;
                };
            }
        }

    public:
        OpenGLShader(std::string _name, std::string vertexShaderPath, std::string fragmentShaderPath, std::string geometryShaderPath = "")
        {
            name = _name;
            std::string vertexShaderCode;
            std::string fragmentShaderCode;
            std::string geometryShaderCode;

            std::ifstream vShaderFile;
            std::ifstream fShaderFile;
            std::ifstream gShaderFile;

            vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
            fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
            gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

            try
            {
                vShaderFile.open(vertexShaderPath);
                std::stringstream vShaderStream;
                vShaderStream << vShaderFile.rdbuf();
                vShaderFile.close();
                vertexShaderCode = vShaderStream.str();

                fShaderFile.open(fragmentShaderPath);
                std::stringstream fShaderStream;
                fShaderStream << fShaderFile.rdbuf();
                fShaderFile.close();
                fragmentShaderCode = fShaderStream.str();

                if (geometryShaderPath != "")
                {
                    gShaderFile.open(geometryShaderPath);
                    std::stringstream gShaderStream;
                    gShaderStream << gShaderFile.rdbuf();
                    gShaderFile.close();
                    geometryShaderCode = gShaderStream.str();
                }
            }
            catch (std::ifstream::failure e)
            {
                std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
            }
            const char *vShaderCode = vertexShaderCode.c_str();
            const char *fShaderCode = fragmentShaderCode.c_str();

            unsigned int vertexShader, fragmentShader, geometryShader;

            vertexShader = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertexShader, 1, &vShaderCode, NULL);
            glCompileShader(vertexShader);
            checkErrors(vertexShader, "VERTEX");

            fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
            glCompileShader(fragmentShader);
            checkErrors(fragmentShader, "FRAGMENT");

            if (geometryShaderPath != "")
            {
                const char *gShaderCode = geometryShaderCode.c_str();
                geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
                glShaderSource(geometryShader, 1, &gShaderCode, NULL);
                glCompileShader(geometryShader);
                checkErrors(geometryShader, "GEOMETRY");
            }

            ID = glCreateProgram();
            glAttachShader(ID, vertexShader);
            glAttachShader(ID, fragmentShader);

            if (geometryShaderPath != "")
                glAttachShader(ID, geometryShader);

            glLinkProgram(ID);
            checkErrors(ID, "PROGRAM");

            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
            if (geometryShaderPath != "")
                glDeleteShader(geometryShader);
        }
        
        void use()
        {
            glUseProgram(ID);
        }
        void setBool(const std::string &name, bool value) const
        {
            glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
        }
        void setInt(const std::string &name, int value) const
        {
            glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
        }
        void setFloat(const std::string &name, float value) const
        {
            glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
        }
        void setVec2(const std::string &name, const glm::vec2 &value) const
        {
            glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
        }
        void setVec2(const std::string &name, float x, float y) const
        {
            glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
        }
        void setVec3(const std::string &name, const glm::vec3 &value) const
        {
            glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
        }
        void setVec3(const std::string &name, float x, float y, float z) const
        {
            glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
        }
        void setVec4(const std::string &name, const glm::vec4 &value) const
        {
            glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
        }
        void setVec4(const std::string &name, float x, float y, float z, float w) const
        {
            glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
        }
        void setMat2(const std::string &name, const glm::mat2 &mat) const
        {
            glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
        }
        void setMat3(const std::string &name, const glm::mat3 &mat) const
        {
            glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
        }
        void setMat4(const std::string &name, const glm::mat4 &mat) const
        {
            glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
        }
    };
} // namespace Snowflake
