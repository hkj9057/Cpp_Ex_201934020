#include <GLFW/glfw3.h> 
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include <iostream>

#pragma comment(lib,"OpenGL32") 

static GLuint texName;

namespace JunSeok_Game
{
    typedef struct tagBITMAPHEADER {
        BITMAPFILEHEADER bf;
        BITMAPINFOHEADER bi;
        RGBQUAD hRGB[256];
    }BITMAPHEADER;

    BYTE* LoadBitmapFile(BITMAPHEADER* bitmapHeader, int* imgSize, const char* filename)
    {
        FILE* fp = fopen(filename, "rb");	//������ �����б���� ����
        if (fp == NULL)
        {
            printf("���Ϸε��� �����߽��ϴ�.\n");	//fopen�� �����ϸ� NULL���� ����
            return NULL;
        }
        else
        {
            fread(&bitmapHeader->bf, sizeof(BITMAPFILEHEADER), 1, fp);	//��Ʈ��������� �б�
            fread(&bitmapHeader->bi, sizeof(BITMAPINFOHEADER), 1, fp);	//��Ʈ��������� �б�
            fread(&bitmapHeader->hRGB, sizeof(RGBQUAD), 256, fp);	//�����ȷ�Ʈ �б�

            int imgSizeTemp = bitmapHeader->bi.biWidth * bitmapHeader->bi.biHeight;	//�̹��� ������ ���
            *imgSize = imgSizeTemp;	// �̹��� ����� ���� ������ �Ҵ�

            BYTE* image = (BYTE*)malloc(sizeof(BYTE) * imgSizeTemp);	//�̹���ũ�⸸ŭ �޸��Ҵ�
            fread(image, sizeof(BYTE), imgSizeTemp, fp);//�̹��� ũ�⸸ŭ ���Ͽ��� �о����
            fclose(fp);

            return image;
        }
    }

    void init(void)
    {
       // glClearColor(0.0, 0.0, 0.0, 0.0);

        BITMAPHEADER originalHeader;	//��Ʈ���� ����κ��� ���Ͽ��� �о� ������ ����ü
        int imgSize;			//�̹����� ũ�⸦ ������ ����
        BYTE* image = LoadBitmapFile(&originalHeader, &imgSize, "Image.bmp"); //��Ʈ�������� �о� ȭ�������� ����
        if (image == NULL) return;
        //���� �б⿡ �����ϸ� ���α׷� ����

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        glGenTextures(1, &texName);
        glBindTexture(GL_TEXTURE_2D, texName);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
            GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
            GL_NEAREST);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 512, 512, 0, GL_RED, GL_BYTE, image);
    }

    class RenderGlfw
    {
    public:

        GLFWwindow* window;
        //BYTE B = NULL;
        //BYTE G = NULL;
        //BYTE R = NULL;

        void GlfwStart()
        {
            glfwSetErrorCallback(error_callback);
            if (!glfwInit())
                exit(EXIT_FAILURE);
            window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
            if (!window)
            {
                glfwTerminate();
                exit(EXIT_FAILURE);
            }
            glfwMakeContextCurrent(window);
            glfwSetKeyCallback(window, key_callback);

            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            init();
        }

        void DrawImage()
        {
                
                glEnable(GL_TEXTURE_2D);

                glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
                glBindTexture(GL_TEXTURE_2D, texName);
                
                glBegin(GL_TRIANGLES);

                glColor3f(1.0f, 0.0f, 0.0f);
                glVertex2f(-1.0f, -1.0f);
                glColor3f(1.0f, 0.0f, 0.0f);
                glVertex2f(-1.0f, 1.0f);
                glColor3f(1.0f, 0.0f, 0.0f);
                glVertex2f(1.0f, -1.0f);

                glBegin(GL_TRIANGLES);

                glColor3f(1.0f, 0.0f, 0.0f);
                glVertex2f(-1.0f, 1.0f);
                glColor3f(1.0f, 0.0f, 0.0f);
                glVertex2f(1.0f, 1.0f);
                glColor3f(1.0f, 0.0f, 0.0f);
                glVertex2f(1.0f, -1.0f);

                //glEnd();
                
           
        }

        void EndGlfw()
        {
            glfwDestroyWindow(window);
            glfwTerminate();
            exit(EXIT_SUCCESS);
        }

        void Draw(float x, float y, float color)
        {
            glClear(GL_COLOR_BUFFER_BIT);

            glPointSize(20);
            glBegin(GL_POINTS); 
           
            glColor3f(1.0f, color, 0.0f);
            glVertex2f(x, y);
        }
        void SwapBuffer()

        {
            glEnd();
            glFlush();
            glDisable(GL_TEXTURE_2D);
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
        static void error_callback(int error, const char* description)
        {
            fputs(description, stderr);
        }

        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
                glfwSetWindowShouldClose(window, GL_TRUE);
        }
        
    };
}