
/****************************************************************************

    CarGL (Objects.cpp)

    Pr�ctica de Gr�ficos por Computador (Grado Ingenier�a Multimedia)
  -----------------------------------------------------------------------

    Noviembre 2012 (C) Juan Antonio Puchol Garc�a (puchol@dccia.ua.es)

 ****************************************************************************/


#include "Objects.h"
#include <GL/glui.h>

#include "load3ds.c"
#include "loadjpeg.c"

// Variable para inicializar los vectores correpondientes con los valores iniciales
GLfloat light0_ambient_c[4] = {0.2f, 0.2f, 0.2f, 1.0f};
GLfloat light0_diffuse_c[4] = {0.8f, 0.8f, 0.8f, 1.0f};
GLfloat light0_specular_c[4] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat light0_position_c[4] = {-50.0f, 5.0f, 0.0f, 1.0f};

GLfloat light1_ambient_c[4] = {0.2f, 0.2f, 0.2f, 1.0f};
GLfloat light1_diffuse_c[4] = {0.8f, 0.8f, 0.8f, 1.0f};
GLfloat light1_specular_c[4] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat light1_position_c[4] = {0.0f, 100.0f, 10.0f, 1.0f};

GLfloat mat_ambient_c[4] = {0.7f, 0.7f, 0.7f, 1.0f};
GLfloat mat_diffuse_c[4] = {0.8f, 0.8f, 0.8f, 1.0f};
GLfloat mat_specular_c[4] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat high_shininess_c[1] = {100.0f};

// Matriz de 4x4 = (I)
float view_rotate_c[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
float view_position_c[3] = {0.0, -2.0, -9.0};

float colores_c[2][4] = {
    {0.8, 0.5, 0.0, 1.0},
    {0.5, 0.5, 0.5, 1.0}
};

//************************************************************** Variables de clase

TEscena escena;
TGui gui;

//************************************************************** Clase TPrimitiva

TPrimitiva::TPrimitiva(int DL, int t) {
    ID = DL;
    tipo = t;

    sx = sy = sz = 1;
    rx = ry = rz = 0;
    switch (tipo) {
        case CARRETERA_ID:
        { // Creaci�n de la carretera

            tx = -2;
            ty = 0;
            tz = 0;
            rr = 0;

            memcpy(colores, colores_c, 8 * sizeof (float));

            //************************ Cargar modelos ***********************************
            int num_vertices = 0;

            float* modelo = Load3DS("../../Modelos/carretera.3ds", &num_vertices);

            glNewList(ID + CALZADA, GL_COMPILE);
            glBegin(GL_TRIANGLES);
            for (int i = 0; i < num_vertices; i++) {
                glNormal3fv((float*) & modelo[i << 3] + 3);
                glTexCoord2fv((float*) & modelo[i << 3] + 6);
                glVertex3fv((float*) & modelo[i << 3]);
            }
            glEnd();
            glEndList();

            // Liberamos la memoria una vez creada la Display List,
            free(modelo);

            num_vertices = 0;

            modelo = Load3DS("../../Modelos/carretera_lineas.3ds", &num_vertices);

            glNewList(ID + LINEAS, GL_COMPILE);
            glBegin(GL_TRIANGLES);
            for (int i = 0; i < num_vertices; i++) {
                glNormal3fv((float*) & modelo[i << 3] + 3);
                glTexCoord2fv((float*) & modelo[i << 3] + 6);
                glVertex3fv((float*) & modelo[i << 3]);
            }
            glEnd();
            glEndList();

            // Liberamos la memoria una vez creada la Display List,
            free(modelo);
            break;
        }
        case ACERAS_ID:
        { // Creaci�n de la carretera

            tx = -2;
            ty = 0;
            tz = 0;
            rr = 0;

            memcpy(colores, colores_c, 8 * sizeof (float));

            //************************ Cargar modelos ***********************************
            int num_vertices = 0;

            float* modelo = Load3DS("../../Modelos/aceras.3ds", &num_vertices);

            glNewList(ID, GL_COMPILE);
            glBegin(GL_TRIANGLES);
            for (int i = 0; i < num_vertices; i++) {
                glNormal3fv((float*) & modelo[i << 3] + 3);
                glTexCoord2fv((float*) & modelo[i << 3] + 6);
                glVertex3fv((float*) & modelo[i << 3]);
            }
            glEnd();
            glEndList();

            // Liberamos la memoria una vez creada la Display List,
            free(modelo);
            break;
        }
        case FAROLA_ID:
        { // Creaci�n de la carretera

            tx = 0;
            ty = 0;
            tz = 0;
            rr = 0;

            memcpy(colores, colores_c, 8 * sizeof (float));

            //************************ Cargar modelos ***********************************
            int num_vertices = 0;

            float* modelo = Load3DS("../../Modelos/farolas.3ds", &num_vertices);

            glNewList(ID, GL_COMPILE);
            glBegin(GL_TRIANGLES);
            for (int i = 0; i < num_vertices; i++) {
                glNormal3fv((float*) & modelo[i << 3] + 3);
                glTexCoord2fv((float*) & modelo[i << 3] + 6);
                glVertex3fv((float*) & modelo[i << 3]);
            }
            glEnd();
            glEndList();

            // Liberamos la memoria una vez creada la Display List,
            free(modelo);
            break;
        }
        case RELOJ_ID:
        { // Creaci�n de la carretera

            tx = 1;
            ty = 5;
            tz = 0;
            rr = 0;

            memcpy(colores, colores_c, 8 * sizeof (float));

            //************************ Cargar modelos ***********************************
            int num_vertices = 0;

            float* modelo = Load3DS("../../Modelos/reloj.3ds", &num_vertices);

            glNewList(ID, GL_COMPILE);
            glBegin(GL_TRIANGLES);
            for (int i = 0; i < num_vertices; i++) {
                glNormal3fv((float*) & modelo[i << 3] + 3);
                glTexCoord2fv((float*) & modelo[i << 3] + 6);
                glVertex3fv((float*) & modelo[i << 3]);
            }
            glEnd();
            glEndList();

            // Liberamos la memoria una vez creada la Display List,
            free(modelo);
            break;
        }
        case COMISARIA_ID:
        { // Creaci�n del coche

            tx = 0;
            ty = 0;
            tz = 0;
            rr = 0;

            memcpy(colores, colores_c, 8 * sizeof (float));

            //************************ Cargar modelos ***********************************
            int num_vertices = 0;

            float* modelo = Load3DS("../../Modelos/comisaria_bloques.3ds", &num_vertices);

            glNewList(ID + COM_BLOQUES, GL_COMPILE);
            glBegin(GL_TRIANGLES);
            for (int i = 0; i < num_vertices; i++) {
                glNormal3fv((float*) & modelo[i << 3] + 3);
                glTexCoord2fv((float*) & modelo[i << 3] + 6);
                glVertex3fv((float*) & modelo[i << 3]);
            }
            glEnd();
            glEndList();

            // Liberamos la memoria una vez creada la Display List,
            free(modelo);

            num_vertices = 0;
            modelo = Load3DS("../../Modelos/comisaria_cristal.3ds", &num_vertices);

            glNewList(ID + COM_CRISTAL, GL_COMPILE);
            glBegin(GL_TRIANGLES);
            for (int i = 0; i < num_vertices; i++) {
                glNormal3fv((float*) & modelo[i << 3] + 3);
                glTexCoord2fv((float*) & modelo[i << 3] + 6);
                glVertex3fv((float*) & modelo[i << 3]);
            }
            glEnd();
            glEndList();

            // Liberamos la memoria una vez creada la Display List,
            free(modelo);

            num_vertices = 0;
            modelo = Load3DS("../../Modelos/comisaria_puerta.3ds", &num_vertices);

            glNewList(ID + COM_PUERTA, GL_COMPILE);
            glBegin(GL_TRIANGLES);
            for (int i = 0; i < num_vertices; i++) {
                glNormal3fv((float*) & modelo[i << 3] + 3);
                glTexCoord2fv((float*) & modelo[i << 3] + 6);
                glVertex3fv((float*) & modelo[i << 3]);
            }
            glEnd();
            glEndList();

            // Liberamos la memoria una vez creada la Display List,
            free(modelo);

            num_vertices = 0;
            modelo = Load3DS("../../Modelos/comisaria_columnas.3ds", &num_vertices);

            glNewList(ID + COM_COLUMNAS, GL_COMPILE);
            glBegin(GL_TRIANGLES);
            for (int i = 0; i < num_vertices; i++) {
                glNormal3fv((float*) & modelo[i << 3] + 3);
                glTexCoord2fv((float*) & modelo[i << 3] + 6);
                glVertex3fv((float*) & modelo[i << 3]);
            }
            glEnd();
            glEndList();

            // Liberamos la memoria una vez creada la Display List,
            free(modelo);
            break;
        }
        case VIVIENDAS_ID:
        { // Creaci�n del coche

            tx = 0;
            ty = 0;
            tz = 0;
            rr = 0;

            memcpy(colores, colores_c, 8 * sizeof (float));

            //************************ Cargar modelos ***********************************
            int num_vertices = 0;

            float* modelo = Load3DS("../../Modelos/viviendas_bloques.3ds", &num_vertices);

            glNewList(ID + VIV_BLOQUES, GL_COMPILE);
            glBegin(GL_TRIANGLES);
            for (int i = 0; i < num_vertices; i++) {
                glNormal3fv((float*) & modelo[i << 3] + 3);
                glTexCoord2fv((float*) & modelo[i << 3] + 6);
                glVertex3fv((float*) & modelo[i << 3]);
            }
            glEnd();
            glEndList();

            // Liberamos la memoria una vez creada la Display List,
            free(modelo);

            num_vertices = 0;
            modelo = Load3DS("../../Modelos/viviendas_cristal.3ds", &num_vertices);

            glNewList(ID + VIV_CRISTAL, GL_COMPILE);
            glBegin(GL_TRIANGLES);
            for (int i = 0; i < num_vertices; i++) {
                glNormal3fv((float*) & modelo[i << 3] + 3);
                glTexCoord2fv((float*) & modelo[i << 3] + 6);
                glVertex3fv((float*) & modelo[i << 3]);
            }
            glEnd();
            glEndList();

            // Liberamos la memoria una vez creada la Display List,
            free(modelo);

            num_vertices = 0;
            modelo = Load3DS("../../Modelos/viviendas_puertas.3ds", &num_vertices);

            glNewList(ID + VIV_PUERTA, GL_COMPILE);
            glBegin(GL_TRIANGLES);
            for (int i = 0; i < num_vertices; i++) {
                glNormal3fv((float*) & modelo[i << 3] + 3);
                glTexCoord2fv((float*) & modelo[i << 3] + 6);
                glVertex3fv((float*) & modelo[i << 3]);
            }
            glEnd();
            glEndList();

            // Liberamos la memoria una vez creada la Display List,
            free(modelo);

            break;
        }
        case VEGETACION_ID:
        { // Creaci�n del coche

            tx = 0;
            ty = 0;
            tz = 0;
            rr = 0;

            memcpy(colores, colores_c, 8 * sizeof (float));

            //************************ Cargar modelos ***********************************
            int num_vertices = 0;

            float* modelo = Load3DS("../../Modelos/vegetacion_troncos.3ds", &num_vertices);

            glNewList(ID + TRONCO, GL_COMPILE);
            glBegin(GL_TRIANGLES);
            for (int i = 0; i < num_vertices; i++) {
                glNormal3fv((float*) & modelo[i << 3] + 3);
                glTexCoord2fv((float*) & modelo[i << 3] + 6);
                glVertex3fv((float*) & modelo[i << 3]);
            }
            glEnd();
            glEndList();

            // Liberamos la memoria una vez creada la Display List,
            free(modelo);

            num_vertices = 0;
            modelo = Load3DS("../../Modelos/vegetacion_hojas.3ds", &num_vertices);

            glNewList(ID + HOJAS, GL_COMPILE);
            glBegin(GL_TRIANGLES);
            for (int i = 0; i < num_vertices; i++) {
                glNormal3fv((float*) & modelo[i << 3] + 3);
                glTexCoord2fv((float*) & modelo[i << 3] + 6);
                glVertex3fv((float*) & modelo[i << 3]);
            }
            glEnd();
            glEndList();

            // Liberamos la memoria una vez creada la Display List,
            free(modelo);

            break;
        }
        case PARQUE_ID:
        { // Creaci�n del coche

            tx = 0;
            ty = 0;
            tz = 0;
            rr = 0;

            memcpy(colores, colores_c, 8 * sizeof (float));

            //************************ Cargar modelos ***********************************
            int num_vertices = 0;

            float* modelo = Load3DS("../../Modelos/parque_suelo.3ds", &num_vertices);

            glNewList(ID + P_SUELO, GL_COMPILE);
            glBegin(GL_TRIANGLES);
            for (int i = 0; i < num_vertices; i++) {
                glNormal3fv((float*) & modelo[i << 3] + 3);
                glTexCoord2fv((float*) & modelo[i << 3] + 6);
                glVertex3fv((float*) & modelo[i << 3]);
            }
            glEnd();
            glEndList();

            // Liberamos la memoria una vez creada la Display List,
            free(modelo);

            num_vertices = 0;
            modelo = Load3DS("../../Modelos/parque_agua.3ds", &num_vertices);

            glNewList(ID + P_AGUA, GL_COMPILE);
            glBegin(GL_TRIANGLES);
            for (int i = 0; i < num_vertices; i++) {
                glNormal3fv((float*) & modelo[i << 3] + 3);
                glTexCoord2fv((float*) & modelo[i << 3] + 6);
                glVertex3fv((float*) & modelo[i << 3]);
            }
            glEnd();
            glEndList();

            // Liberamos la memoria una vez creada la Display List,
            free(modelo);

            num_vertices = 0;
            modelo = Load3DS("../../Modelos/parque_puente.3ds", &num_vertices);

            glNewList(ID + P_PUENTE, GL_COMPILE);
            glBegin(GL_TRIANGLES);
            for (int i = 0; i < num_vertices; i++) {
                glNormal3fv((float*) & modelo[i << 3] + 3);
                glTexCoord2fv((float*) & modelo[i << 3] + 6);
                glVertex3fv((float*) & modelo[i << 3]);
            }
            glEnd();
            glEndList();

            // Liberamos la memoria una vez creada la Display List,
            free(modelo);

            break;
        }
        case BANCO_ID:
        { // Creaci�n del coche

            tx = 0;
            ty = 0;
            tz = 0;
            rr = 0;

            memcpy(colores, colores_c, 8 * sizeof (float));

            //************************ Cargar modelos ***********************************
            int num_vertices = 0;

            float* modelo = Load3DS("../../Modelos/bancos_base.3ds", &num_vertices);

            glNewList(ID + BASE, GL_COMPILE);
            glBegin(GL_TRIANGLES);
            for (int i = 0; i < num_vertices; i++) {
                glNormal3fv((float*) & modelo[i << 3] + 3);
                glTexCoord2fv((float*) & modelo[i << 3] + 6);
                glVertex3fv((float*) & modelo[i << 3]);
            }
            glEnd();
            glEndList();

            // Liberamos la memoria una vez creada la Display List,
            free(modelo);

            num_vertices = 0;
            modelo = Load3DS("../../Modelos/bancos_asientos.3ds", &num_vertices);

            glNewList(ID + ASIENTO, GL_COMPILE);
            glBegin(GL_TRIANGLES);
            for (int i = 0; i < num_vertices; i++) {
                glNormal3fv((float*) & modelo[i << 3] + 3);
                glTexCoord2fv((float*) & modelo[i << 3] + 6);
                glVertex3fv((float*) & modelo[i << 3]);
            }
            glEnd();
            glEndList();

            // Liberamos la memoria una vez creada la Display List,
            free(modelo);

            break;
        }
        case DAVID_ID:
        { // Creaci�n del coche

            tx = -12;
            ty = 6;
            tz = -12;
            rr = 0;
            sx = sy = sz = 0.6;
            memcpy(colores, colores_c, 8 * sizeof (float));

            //************************ Cargar modelos ***********************************
            int num_vertices = 0;

            float* modelo = Load3DS("../../Modelos/david_pedestal.3ds", &num_vertices);

            glNewList(ID + PEDESTAL, GL_COMPILE);
            glBegin(GL_TRIANGLES);
            for (int i = 0; i < num_vertices; i++) {
                glNormal3fv((float*) & modelo[i << 3] + 3);
                glTexCoord2fv((float*) & modelo[i << 3] + 6);
                glVertex3fv((float*) & modelo[i << 3]);
            }
            glEnd();
            glEndList();

            // Liberamos la memoria una vez creada la Display List,
            free(modelo);

            num_vertices = 0;
            modelo = Load3DS("../../Modelos/david_figura.3ds", &num_vertices);

            glNewList(ID + FIGURA, GL_COMPILE);
            glBegin(GL_TRIANGLES);
            for (int i = 0; i < num_vertices; i++) {
                glNormal3fv((float*) & modelo[i << 3] + 3);
                glTexCoord2fv((float*) & modelo[i << 3] + 6);
                glVertex3fv((float*) & modelo[i << 3]);
            }
            glEnd();
            glEndList();

            // Liberamos la memoria una vez creada la Display List,
            free(modelo);


            break;
        }
        case STOP_ID:
        { // Creaci�n del coche

            tx = 0;
            ty = 0;
            tz = 0;
            rr = 0;
            sx = sy = sz = 0;
            memcpy(colores, colores_c, 8 * sizeof (float));

            //************************ Cargar modelos ***********************************
            int num_vertices = 0;

            float* modelo = Load3DS("../../Modelos/stop_base.3ds", &num_vertices);

            glNewList(ID + S_BASE, GL_COMPILE);
            glBegin(GL_TRIANGLES);
            for (int i = 0; i < num_vertices; i++) {
                glNormal3fv((float*) & modelo[i << 3] + 3);
                glTexCoord2fv((float*) & modelo[i << 3] + 6);
                glVertex3fv((float*) & modelo[i << 3]);
            }
            glEnd();
            glEndList();

            // Liberamos la memoria una vez creada la Display List,
            free(modelo);

            num_vertices = 0;
            modelo = Load3DS("../../Modelos/stop_signal.3ds", &num_vertices);

            glNewList(ID + S_SIGNAL, GL_COMPILE);
            glBegin(GL_TRIANGLES);
            for (int i = 0; i < num_vertices; i++) {
                glNormal3fv((float*) & modelo[i << 3] + 3);
                glTexCoord2fv((float*) & modelo[i << 3] + 6);
                glVertex3fv((float*) & modelo[i << 3]);
            }
            glEnd();
            glEndList();

            // Liberamos la memoria una vez creada la Display List,
            free(modelo);


            break;
        }
        case COCHE_ID:
        { // Creaci�n del coche

            tx = -2;
            ty = 2;
            tz = -30;
            rr = 0;

            memcpy(colores, colores_c, 8 * sizeof (float));

            //************************ Cargar modelos ***********************************
            int num_vertices = 0;

            float* modelo = Load3DS("../../Modelos/furgoneta_chapa.3ds", &num_vertices);

            glNewList(ID + CHAPA, GL_COMPILE);
            glBegin(GL_TRIANGLES);
            for (int i = 0; i < num_vertices; i++) {
                glNormal3fv((float*) & modelo[i << 3] + 3);
                glTexCoord2fv((float*) & modelo[i << 3] + 6);
                glVertex3fv((float*) & modelo[i << 3]);
            }
            glEnd();
            glEndList();

            // Liberamos la memoria una vez creada la Display List,
            free(modelo);

            num_vertices = 0;
            modelo = Load3DS("../../Modelos/rueda.3ds", &num_vertices);

            glNewList(ID + RUEDA, GL_COMPILE);
            glBegin(GL_TRIANGLES);
            for (int i = 0; i < num_vertices; i++) {
                glNormal3fv((float*) & modelo[i << 3] + 3);
                glTexCoord2fv((float*) & modelo[i << 3] + 6);
                glVertex3fv((float*) & modelo[i << 3]);
            }
            glEnd();
            glEndList();

            // Liberamos la memoria una vez creada la Display List,
            free(modelo);

            num_vertices = 0;
            modelo = Load3DS("../../Modelos/furgoneta_plasticos.3ds", &num_vertices);

            glNewList(ID + PLASTICOS, GL_COMPILE);
            glBegin(GL_TRIANGLES);
            for (int i = 0; i < num_vertices; i++) {
                glNormal3fv((float*) & modelo[i << 3] + 3);
                glTexCoord2fv((float*) & modelo[i << 3] + 6);
                glVertex3fv((float*) & modelo[i << 3]);
            }
            glEnd();
            glEndList();

            // Liberamos la memoria una vez creada la Display List,
            free(modelo);

            num_vertices = 0;
            modelo = Load3DS("../../Modelos/furgoneta_cristales.3ds", &num_vertices);

            glNewList(ID + CRISTAL, GL_COMPILE);
            glBegin(GL_TRIANGLES);
            for (int i = 0; i < num_vertices; i++) {
                glNormal3fv((float*) & modelo[i << 3] + 3);
                glTexCoord2fv((float*) & modelo[i << 3] + 6);
                glVertex3fv((float*) & modelo[i << 3]);
            }
            glEnd();
            glEndList();

            // Liberamos la memoria una vez creada la Display List,
            free(modelo);

            num_vertices = 0;
            modelo = Load3DS("../../Modelos/furgoneta_luces.3ds", &num_vertices);

            glNewList(ID + LUCES, GL_COMPILE);
            glBegin(GL_TRIANGLES);
            for (int i = 0; i < num_vertices; i++) {
                glNormal3fv((float*) & modelo[i << 3] + 3);
                glTexCoord2fv((float*) & modelo[i << 3] + 6);
                glVertex3fv((float*) & modelo[i << 3]);
            }
            glEnd();
            glEndList();

            // Liberamos la memoria una vez creada la Display List,
            free(modelo);
            break;
        }
            //---------------------- CUSTOM CODE --------------------------/
        case SEMAFORO_ID:
        { // Creaci�n del semaforo

            tx = -2;
            ty = 0;
            tz = 0;
            rr = 0;

            memcpy(colores, colores_c, 8 * sizeof (float));

            //************************ Cargar modelos ***********************************
            int num_vertices = 0;

            float* modelo = Load3DS("../../Modelos/semaforo.3ds", &num_vertices);

            glNewList(ID, GL_COMPILE);
            glBegin(GL_TRIANGLES);
            for (int i = 0; i < num_vertices; i++) {
                glNormal3fv((float*) & modelo[i << 3] + 3);
                glTexCoord2fv((float*) & modelo[i << 3] + 6);
                glVertex3fv((float*) & modelo[i << 3]);
            }
            glEnd();
            glEndList();

            // Liberamos la memoria una vez creada la Display List,
            free(modelo);
            break;
        }


        case ROTONDA_ID:
        { // Creaci�n del semaforo

            tx = -2;
            ty = 0;
            tz = 0;
            rr = 0;

            memcpy(colores, colores_c, 8 * sizeof (float));

            //************************ Cargar modelos ***********************************
            int num_vertices = 0;

            float* modelo = Load3DS("../../Modelos/rotonda.3ds", &num_vertices);

            glNewList(ID, GL_COMPILE);
            glBegin(GL_TRIANGLES);
            for (int i = 0; i < num_vertices; i++) {
                glNormal3fv((float*) & modelo[i << 3] + 3);
                glTexCoord2fv((float*) & modelo[i << 3] + 6);
                glVertex3fv((float*) & modelo[i << 3]);
            }
            glEnd();
            glEndList();

            // Liberamos la memoria una vez creada la Display List,
            free(modelo);
            break;
        }
            //-------------------- END CUSTOM CODE ------------------------//
    } // fin del case
}

void __fastcall TPrimitiva::Render(int seleccion, bool reflejo) {
    switch (tipo) {
        case CARRETERA_ID:
        {
            if (escena.show_road) {
                glPushMatrix();
                glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

                glColor4f(0.1, 0.1, 0.1, 0.8);
                glLoadName(0); // No seleccionable
                glCallList(ID + CALZADA);
                glPopMatrix();
                if (escena.show_roadLines) {
                    glPushMatrix();
                    glTranslated(0, 0.4, 0);
                    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

                    glColor4f(1.0, 1.0, 1.0, 1.0);
                    glLoadName(0); // No seleccionable
                    glCallList(ID + LINEAS);
                    glPopMatrix();
                }
            }
            break;
        }
        case ACERAS_ID:
        {
            if (escena.show_aceras) {
                glPushMatrix();
                glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
                glColor4fv(colores[0]);
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, escena.streetTexture);
                glLoadName(0); // No seleccionable
                glCallList(ID);
                glPopMatrix();
            }
            break;
        }
        case ROTONDA_ID:
        {
            if (escena.show_rotonda) {
                glPushMatrix();
                glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, escena.grassTexture);
                glColor4fv(colores[0]);
                glLoadName(0); // No seleccionable
                glCallList(ID);
                glPopMatrix();
            }
            break;
        }
        case STOP_ID:
        {
            if (escena.show_stop) {
                glPushMatrix();
                glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
                glColor4f(0.7, 0.7, 0.7, 1.0);
                glLoadName(0); // No seleccionable
                glCallList(ID + S_BASE);
                glPopMatrix();

                glPushMatrix();
                glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, escena.stopTexture);
                glColor4f(1.0, 1.0, 1.0, 1.0);
                glLoadName(0); // No seleccionable
                glCallList(ID + S_SIGNAL);
                glPopMatrix();
            }
            break;
        }
        case FAROLA_ID:
        {
            if (escena.show_lampost) {
                glPushMatrix();
                glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
                glColor4f(0.1, 0.1, 0.1, 1.0);

                glLoadName(0); // No seleccionable
                glCallList(ID);
                glPopMatrix();
            }
            break;
        }
        case COMISARIA_ID:
        {
            glPushMatrix();
            // Traslaci�n del coche y ruedas
            glTranslated(tx, ty, tz);
            glScaled(sx, sy, sz);
            if (escena.show_buildings) {
                glPushMatrix();
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, escena.brickTexture);
                glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
                glColor4fv(colores[0]);
                glLoadName(ID);
                glCallList(ID + COM_BLOQUES);
                glPopMatrix();

                glPushMatrix();
                glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
                glColor4fv(colores[1]);
                glLoadName(ID);
                glCallList(ID + COM_CRISTAL);
                glPopMatrix();

                glPushMatrix();
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, escena.marbleTexture);
                glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
                glColor4fv(colores[0]);
                glLoadName(ID);
                glCallList(ID + COM_COLUMNAS);
                glPopMatrix();

                glPushMatrix();
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, escena.doorTexture);
                glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
                glColor4fv(colores[0]);
                glLoadName(ID);
                glCallList(ID + COM_PUERTA);
                glPopMatrix();
            }
            glPopMatrix();
            break;
        }
        case VIVIENDAS_ID:
        {
            glPushMatrix();
            // Traslaci�n del coche y ruedas
            glTranslated(tx, ty, tz);
            glScaled(sx, sy, sz);
            if (escena.show_buildings) {
                glPushMatrix();
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, escena.brick2Texture);
                glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
                glColor4fv(colores[0]);
                glLoadName(ID);
                glCallList(ID + VIV_BLOQUES);
                glPopMatrix();

                glPushMatrix();
                glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
                glColor4fv(colores[1]);
                glLoadName(ID);
                glCallList(ID + VIV_CRISTAL);
                glPopMatrix();

                glPushMatrix();
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, escena.door2Texture);
                glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
                glColor4fv(colores[0]);
                glLoadName(ID);
                glCallList(ID + VIV_PUERTA);
                glPopMatrix();
            }
            glPopMatrix();
            break;
        }
        case BANCO_ID:
        {
            glPushMatrix();
            // Traslaci�n del coche y ruedas
            glTranslated(tx, ty, tz);
            glScaled(sx, sy, sz);
            if (escena.show_benchs) {
                glPushMatrix();
                glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
                glColor4fv(colores[0]);
                glLoadName(ID);
                glCallList(ID + BASE);
                glPopMatrix();

                glPushMatrix();
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, escena.barkTexture);
                glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
                glColor4fv(colores[0]);
                glLoadName(ID);
                glCallList(ID + ASIENTO);
                glPopMatrix();
            }
            glPopMatrix();
            break;
        }
        case VEGETACION_ID:
        {
            glPushMatrix();
            // Traslaci�n del coche y ruedas
            glTranslated(tx, ty, tz);
            glScaled(sx, sy, sz);
            if (escena.show_vegetation) {

                glPushMatrix();
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, escena.barkTexture);
                glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
                glColor4fv(colores[0]);
                glLoadName(ID);
                glCallList(ID + TRONCO);
                glPopMatrix();

                glPushMatrix();
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, escena.leavesTexture);
                glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
                glColor4fv(colores[0]);
                glLoadName(ID);
                glCallList(ID + HOJAS);
                glPopMatrix();
            }
            glPopMatrix();
            break;
        }
        case PARQUE_ID:
        {
            glPushMatrix();
            // Traslaci�n del coche y ruedas
            glTranslated(tx, ty, tz);
            glScaled(sx, sy, sz);
            if (escena.show_vegetation) {

                glPushMatrix();
                glTranslated(0, 0.2, 0);
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, escena.grassTexture);
                glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
                glColor4fv(colores[0]);
                glLoadName(ID);
                glCallList(ID + P_SUELO);
                glPopMatrix();

                glPushMatrix();
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, escena.waterTexture);
                glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
                glColor4fv(colores[0]);
                glLoadName(ID);
                glCallList(ID + P_AGUA);
                glPopMatrix();

                glPushMatrix();
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, escena.bridgeTexture);
                glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
                glColor4fv(colores[0]);
                glLoadName(ID);
                glCallList(ID + P_PUENTE);
                glPopMatrix();
            }
            glPopMatrix();
            break;
        }
        case DAVID_ID:
        {
            glPushMatrix();
            // Traslaci�n del coche y ruedas
            glTranslated(tx, ty, tz);
            glScaled(sx, sy, sz);
            if (escena.show_david) {

                glPushMatrix();

                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, escena.marbleTexture);
                glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
                glColor4fv(colores[0]);
                glLoadName(ID);
                glCallList(ID + FIGURA);
                glPopMatrix();

                glPushMatrix();
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, escena.bridgeTexture);
                glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
                glColor4fv(colores[1]);
                glLoadName(ID);
                glCallList(ID + PEDESTAL);
                glPopMatrix();


            }
            glPopMatrix();
            break;
        }
        case RELOJ_ID:
        {

            if (escena.show_reloj) {
                glPushMatrix();
                glTranslated(tx, ty, tz);
                glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, escena.stoneTexture);
                glColor4fv(colores[0]);
                glLoadName(0); // No seleccionable
                glCallList(ID);
                glPopMatrix();
            }
            break;
        }
        case COCHE_ID:
        {
            glPushMatrix();
            // Traslaci�n del coche y ruedas
            glTranslated(tx, ty, tz);
            glScaled(sx, sy, sz);
            if (escena.show_car) {
                glPushMatrix();
                glScaled(0.25, 0.25, 0.25);
                glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
                glColor4fv(colores[0]);
                glLoadName(ID);
                glCallList(ID + CHAPA);
                glPopMatrix();

                glPushMatrix();
                glScaled(0.25, 0.25, 0.25);
                glTranslated(-7.24, -5, -22.5);
                glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
                glColor4fv(colores[1]);
                glLoadName(ID);
                glCallList(ID + PLASTICOS);
                glPopMatrix();

                glPushMatrix();
                glScaled(0.25, 0.25, 0.25);
                glTranslated(-0.15, 3.8, -6);
                glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
                glColor4fv(colores[2]);
                glLoadName(ID);
                glCallList(ID + CRISTAL);
                glPopMatrix();

                glPushMatrix();
                glScaled(0.25, 0.25, 0.25);
                glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
                glColor4fv(colores[3]);
                glLoadName(ID);
                glCallList(ID + LUCES);
                glPopMatrix();
            }

            if (escena.show_wheels) {

                glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
                glColor4fv(colores [4]);
                glPushMatrix();

                //DELANTERAS
                glTranslated(1.3, -1.4, 3.5);
                glRotated(rr, 1, 0, 0);
                glRotated(180, 0, 0, 1);
                glLoadName(ID);
                glCallList(ID + RUEDA);
                glPopMatrix();

                glPushMatrix();
                glTranslated(-1.3, -1.4, 3.5);
                glRotated(rr, 1, 0, 0);
                glLoadName(ID);
                glCallList(ID + RUEDA);
                glPopMatrix();

                //TRASERAS
                glPushMatrix();
                glTranslated(1.3, -1.4, -1.55);
                glRotated(rr, 1, 0, 0);
                glRotated(180, 0, 0, 1);
                glLoadName(ID);
                glCallList(ID + RUEDA);
                glPopMatrix();

                glPushMatrix();
                glTranslated(-1.3, -1.4, -1.55);
                glRotated(rr, 1, 0, 0);
                glLoadName(ID);
                glCallList(ID + RUEDA);
                glPopMatrix();
            }
            glPopMatrix();
            break;
        }
        case SEMAFORO_ID:
        {
            if (escena.show_semaforo) {
                glPushMatrix();
                glLoadName(0); // No seleccionable
                glCallList(ID);
                glPopMatrix();
            }
            break;
        }
    }
    glDisable(GL_TEXTURE_2D);

}

//************************************************************** Clase TEscena

TEscena::TEscena() {

    seleccion = 0;
    num_objects = 0;
    num_cars = 0;
    num_roads = 0;

    show_car = 1;
    show_wheels = 1;
    show_road = 1;
    show_semaforo = 1;
    show_rotonda = 1;
    show_aceras = 1;
    show_reloj = 1;
    show_buildings = 1;
    show_vegetation = 1;
    show_benchs = 1;
    show_david = 1;
    show_roadLines = 1;
    show_lampost = 1;
    show_stop = 1;
    // live variables usadas por GLUI en TGui
    wireframe = 0;
    z_buffer = 1;
    culling = 1;
    projection = PERSPECTIVE_PROJ;
    ambientLights = 1;
    clockWiseFaces = 0;
    shadowing = 1;
    scale = 1.0;
    xy_aspect = 1;
    last_x = 0;
    last_y = 0;

    move_valid = 0;
    control_pressed = 0;
    space_pressed = 0;
    disable_light_ambient[0] = 0.0f;
    disable_light_ambient[1] = 0.0f;
    disable_light_ambient[2] = 0.0f;
    disable_light_ambient[3] = 1.0f;

    memcpy(view_position, view_position_c, 3 * sizeof (float));
    memcpy(view_rotate, view_rotate_c, 16 * sizeof (float));

    memcpy(light0_ambient, light0_ambient_c, 4 * sizeof (float));

    memcpy(light0_ambient, light0_ambient_c, 4 * sizeof (float));
    memcpy(light0_diffuse, light0_diffuse_c, 4 * sizeof (float));
    memcpy(light0_specular, light0_specular_c, 4 * sizeof (float));
    memcpy(light0_position, light0_position_c, 4 * sizeof (float));

    memcpy(light1_ambient, light1_ambient_c, 4 * sizeof (float));
    memcpy(light1_diffuse, light1_diffuse_c, 4 * sizeof (float));
    memcpy(light1_specular, light1_specular_c, 4 * sizeof (float));
    memcpy(light1_position, light1_position_c, 4 * sizeof (float));

    memcpy(mat_ambient, mat_ambient_c, 4 * sizeof (float));
    memcpy(mat_diffuse, mat_diffuse_c, 4 * sizeof (float));
    memcpy(mat_specular, mat_specular_c, 4 * sizeof (float));
    memcpy(high_shininess, high_shininess_c, 1 * sizeof (float));
}

void __fastcall TEscena::InitGL() {
    int tx, ty, tw, th;
    GLUI_Master.get_viewport_area(&tx, &ty, &tw, &th);

    escena.xy_aspect = (float) tw / (float) th;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, escena.xy_aspect, 1.0, 1000.0);


    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);

    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);

    glEnable(GL_COLOR_MATERIAL);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    // Habilita el z_buffer
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    //stoneTexture = LoadTextureJPEG("../../Texturas/stone_texture.jpg",1);
    //grassTexture = LoadTextureJPEG("../../Texturas/grass_texture.jpg",1);

    int width;
    int height;
    width = height = 894;
    unsigned char * tex = LoadJPEG("../../Texturas/grass_texture.jpg", &width, &height);
    glGenTextures(1, &grassTexture);
    glBindTexture(GL_TEXTURE_2D, grassTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    width = height = 894;
    tex = LoadJPEG("../../Texturas/stone_texture.jpg", &width, &height);
    glGenTextures(1, &stoneTexture);
    glBindTexture(GL_TEXTURE_2D, stoneTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    width = height = 600;
    tex = LoadJPEG("../../Texturas/street_texture.jpg", &width, &height);
    glGenTextures(1, &streetTexture);
    glBindTexture(GL_TEXTURE_2D, streetTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    width = height = 1111;
    tex = LoadJPEG("../../Texturas/marble_texture.jpg", &width, &height);
    glGenTextures(1, &marbleTexture);
    glBindTexture(GL_TEXTURE_2D, marbleTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    width = 863;
    height = 996;
    tex = LoadJPEG("../../Texturas/door_texture.jpg", &width, &height);
    glGenTextures(1, &doorTexture);
    glBindTexture(GL_TEXTURE_2D, doorTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    width = height = 1000;
    tex = LoadJPEG("../../Texturas/building_texture.jpg", &width, &height);
    glGenTextures(1, &brickTexture);
    glBindTexture(GL_TEXTURE_2D, brickTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    width = height = 500;
    tex = LoadJPEG("../../Texturas/bark_texture.jpg", &width, &height);
    glGenTextures(1, &barkTexture);
    glBindTexture(GL_TEXTURE_2D, barkTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    width = height = 512;
    tex = LoadJPEG("../../Texturas/leaves_texture.jpg", &width, &height);
    glGenTextures(1, &leavesTexture);
    glBindTexture(GL_TEXTURE_2D, leavesTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    width = height = 256;
    tex = LoadJPEG("../../Texturas/water_texture.jpg", &width, &height);
    glGenTextures(1, &waterTexture);
    glBindTexture(GL_TEXTURE_2D, waterTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    width = 900;
    height = 602;
    tex = LoadJPEG("../../Texturas/bridge_texture.jpg", &width, &height);
    glGenTextures(1, &bridgeTexture);
    glBindTexture(GL_TEXTURE_2D, bridgeTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    width = 512;
    height = 512;
    tex = LoadJPEG("../../Texturas/wall_texture.jpg", &width, &height);
    glGenTextures(1, &brick2Texture);
    glBindTexture(GL_TEXTURE_2D, brick2Texture);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    width = 258;
    height = 525;
    tex = LoadJPEG("../../Texturas/door2_texture.jpg", &width, &height);
    glGenTextures(1, &door2Texture);
    glBindTexture(GL_TEXTURE_2D, door2Texture);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    width = 1811;
    height = 1811;
    tex = LoadJPEG("../../Texturas/stop_texture.jpg", &width, &height);
    glGenTextures(1, &stopTexture);
    glBindTexture(GL_TEXTURE_2D, stopTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

}

/************************** TEscena::AddCar(TPrimitiva *car) *****************/

void __fastcall TEscena::AddCar(TPrimitiva *car) {
    cars[num_cars] = car;
    num_cars++;
}

/******************** TEscena::AddObject(TPrimitiva *object) *****************/

void __fastcall TEscena::AddObject(TPrimitiva *object) {
    objects[num_objects] = object;
    num_objects++;
}

/******************** TEscena::AddRoad(TPrimitiva *object) *****************/

void __fastcall TEscena::AddRoad(TPrimitiva *object) {
    roads[num_roads] = object;
    num_roads++;
}

/******************** TPrimitiva *TEscena::GetCar(int id) ********************/

TPrimitiva __fastcall *TEscena::GetCar(int id) {
    TPrimitiva *p = NULL;

    for (int i = 0; i < num_cars; i++) {
        if (cars[i]->ID == id) {
            p = cars[i];
        }

    }
    return (p);
}

/******************** TEscena::RenderCars() **********************************/

void __fastcall TEscena::RenderCars(bool reflejo) {

    for (int i = 0; i < num_cars; i++) {
        cars[i]->Render(seleccion, reflejo);
    }
}

/******************** TEscena::RenderCars() **********************************/

void __fastcall TEscena::RenderObjects(bool reflejo) {

    for (int i = 0; i < num_objects; i++) {
        objects[i]->Render(seleccion, reflejo);
    }
}

/******************** TEscena::RenderRoads() **********************************/

void __fastcall TEscena::RenderRoads(bool reflejo) {

    for (int i = 0; i < num_roads; i++) {
        roads[i]->Render(seleccion, reflejo);
    }
}

/***************************************** TEscena::Render() *****************/

void __fastcall TEscena::Render() {
    //REFLEJO
    // Clear Screen, Depth Buffer & Stencil Buffer
    if (escena.ambientLights) {
        glClearColor(0.0, 0.7, 0.9, 1.0); //Color Azul
        glLightfv(GL_LIGHT0, GL_AMBIENT, escena.light0_ambient);
        glLightfv(GL_LIGHT1, GL_AMBIENT, escena.light1_ambient);
    } else {
        glClearColor(0.0, 0.7, 0.9, 1.0); //Color Azul
        glLightfv(GL_LIGHT0, GL_AMBIENT, escena.disable_light_ambient);
        glLightfv(GL_LIGHT1, GL_AMBIENT, escena.disable_light_ambient);
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    // Clip Plane Equations
    double eqr[] = {0.0f, -1.0f, 0.0f, 0.0f}; // Plane Equation To Use For The Reflected Objects


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Transformación del escenario
    glTranslatef(view_position[0], view_position[1], view_position[2]); // Traslación
    glMultMatrixf(view_rotate); // Rotación
    glScalef(scale, scale, scale);

    glColorMask(0, 0, 0, 0); // Set Color Mask
    glEnable(GL_STENCIL_TEST); // Enable Stencil Buffer For "marking" The Floor
    glStencilFunc(GL_ALWAYS, 1, 1); // Always Passes, 1 Bit Plane, 1 As Mask
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE); // We Set The Stencil Buffer To 1 Where We Draw Any Polygon
    // Keep If Test Fails, Keep If Test Passes But Buffer Test Fails
    // Replace If Test Passes
    glDisable(GL_DEPTH_TEST);
    // Disable Depth Testin

    if (escena.clockWiseFaces)glFrontFace(GL_CW);
    else glFrontFace(GL_CCW);


    if (escena.culling)glEnable(GL_CULL_FACE); //ACTIVO CULLING
    RenderRoads(seleccion); //DIBUJO										// Draw The Floor (Draws To The Stencil Buffer)
    glDisable(GL_CULL_FACE); //DESACTIVO CULL

    if (escena.z_buffer)glEnable(GL_DEPTH_TEST);

    glColorMask(1, 1, 1, 1); // Set Color Mask to TRUE, TRUE, TRUE, TRUE
    glStencilFunc(GL_EQUAL, 1, 1); // We Draw Only Where The Stencil Is 1
    // (I.E. Where The Floor Was Drawn)
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP); // Don't Change The Stencil Buffer

    glPushMatrix(); // Push The Matrix Onto The Stack
    glScalef(1.0f, -1.0f, 1.0f); // Mirror Y Axis
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);

    RenderObjects(seleccion);
    RenderCars(seleccion);


    glPopMatrix(); // Pop The Matrix Off The Stack
    glDisable(GL_CLIP_PLANE0); // Disable Clip Plane For Drawing The Floor
    glDisable(GL_STENCIL_TEST); // We Don't Need The Stencil Buffer Any More (Disable)

    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);

    glEnable(GL_BLEND); // Enable Blending (Otherwise The Reflected Object Wont Show)
    glDisable(GL_LIGHTING); // Since We Use Blending, We Disable Lighting
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Blending Based On Source Alpha And 1 Minus Dest Alpha
    RenderRoads(seleccion); //DIBUJO
    glEnable(GL_LIGHTING); // Enable Lighting
    glDisable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    RenderObjects(seleccion);
    RenderCars(seleccion); // Draw The Ball
    glutSwapBuffers();
    glDisable(GL_BLEND);

}

// Selecciona un objeto a trav�s del rat�n

void __fastcall TEscena::Pick3D(int mouse_x, int mouse_y) {
    // formato de buffer, cada cuatro posiciones almacena:
    //      buffer[i]   = n�mero de objetos
    //      buffer[i+1] = profundidad m�nima
    //      buffer[i+2] = profuncidad m�xima
    //      buffer[i+3] = nombre de la pila

    // Tama�o de la ventana (Viewport) [0] es <x>, [1] es <y>, [2] es <ancho>, [3] es <alto>
    GLint viewport[4];
    GLuint buffer[2048];
    GLint hits;
    int profundidad;
    char cad[80];
    int tx, ty, tw, th;

    seleccion = 0;
    GLUI_Master.get_viewport_area(&tx, &ty, &tw, &th);
    glViewport(tx, ty, tw, th);

    // Establece el vector <viewport> al tama�o y posici�n relativa a la ventana de visualizaci�n
    glGetIntegerv(GL_VIEWPORT, viewport);
    glSelectBuffer(2048, buffer); // usa <buffer> como nuestro vector para seleccionar

    (void) glRenderMode(GL_SELECT); // Modo Render en SELECCION

    glInitNames(); // Inicializa la pila de nombres
    glPushName(0); // Apila 0 (al menos una entrada) en la pila
    glMatrixMode(GL_PROJECTION); // Selecciona el modo proyecci�n
    glPushMatrix(); // Apila la matriz de proyecci�n
    glLoadIdentity(); // Resetea la matriz (matriz identidad)
    // Crea una matriz que agranda la peque�a porci�n de pantalla donde se ecuentra el rat�n
    gluPickMatrix((GLdouble) mouse_x, (GLdouble) (viewport[3] + viewport[1] - mouse_y), 1.0f, 1.0f, viewport);

    // Aplica la Matriz de Perspectiva
    //gluPerspective(45.0f, (GLfloat) (viewport[2]-viewport[0])/(GLfloat) (viewport[3]-viewport[1]), 1.0, 1000.0);
    gluPerspective(45, xy_aspect, 1.0, 1000.0);
    glMatrixMode(GL_MODELVIEW); // Selecciona la matriz de ModelView
    Render(); // Renderiza los objetos a seleccionar
    glMatrixMode(GL_PROJECTION); // Selecciona la matriz de Proyecci�n
    glPopMatrix(); // Recupera la matriz de Proyecci�n
    glMatrixMode(GL_MODELVIEW); // Selecciona la matriz de ModelView
    hits = glRenderMode(GL_RENDER); // Cambia a modo RENDERIZAR

    if (hits > 0) // Si hay m�s de un objeto
        // (Hits=n�mero de objetos que se hallan en la posici�n del rat�n)
    {
        seleccion = buffer[3]; // Coge como selecci�n el primer objeto de la lista
        profundidad = buffer[1]; // Calcula su profundidad

        for (int i = 1; i < hits; i++) // Recorre todos los objetos
        {
            // Si el objetos est� m�s cerca que el seleccionado ahora
            if (buffer[i * 4 + 1] < GLuint(profundidad)) {
                seleccion = buffer[i * 4 + 3]; // Selecciona dicho objeto
                profundidad = buffer[i * 4 + 1]; // Calcula su profundidad
            }
        }
    }
    sprintf(cad, "%03d [%03d, %03d]", seleccion, mouse_x, mouse_y);
    gui.sel_tex->set_text(cad);
}

//************************************************************** Clase TGui

TGui::TGui() {
    enable_panel2 = 1;
    light0_enabled = 1;
    light1_enabled = 1;
    light0_intensity = 0.8;
    light1_intensity = 0.8;
}

void controlCallback(int control) {
    gui.ControlCallback(control);
}

void __fastcall TGui::Init(int main_window) {

    /****************************************************/
    /*        C�digo con el interfaz Gr�fico GLUI       */
    /****************************************************/
    printf("GLUI version: %3.2f\n", GLUI_Master.get_version());

    window_id = main_window;

    /*** Crea a ventana lateral ***/
    glui = GLUI_Master.create_glui_subwindow(window_id, GLUI_SUBWINDOW_RIGHT);

    /*** MODO DE VISUALIZACION***/
    GLUI_Panel *visualization_mode = new GLUI_Rollout(glui, "Modo", false);

    vis_group = glui->add_radiogroup_to_panel(visualization_mode, &escena.projection, PROJECTION_ID, controlCallback);
    GLUI_RadioButton *persp_radio = glui->add_radiobutton_to_group(vis_group, "Perspectiva");
    GLUI_RadioButton *orto_radio = glui->add_radiobutton_to_group(vis_group, "Ortogonal");

    new GLUI_StaticText(glui, "");

    obj_panel = new GLUI_Rollout(glui, "Propiedades", false);

    /***** Control para las propiedades de escena *****/

    new GLUI_Checkbox(obj_panel, "Modo Alambrico", &escena.wireframe, WIREFRAME_ID, controlCallback);
    new GLUI_Checkbox(obj_panel, "Z Buffer", &escena.z_buffer, ZBUFFER_ID, controlCallback);
    new GLUI_Checkbox(obj_panel, "Culling", &escena.culling, 1, controlCallback);
    new GLUI_Checkbox(obj_panel, "Luz Ambiente", &escena.ambientLights, 1, controlCallback);
    new GLUI_Checkbox(obj_panel, "Sentido Horario", &escena.clockWiseFaces, 1, controlCallback);

    new GLUI_StaticText(glui, "");
    /*** CAMARAS***/
    GLUI_Panel *camera_panel = new GLUI_Rollout(glui, "Camaras", false);
    GLUI_RadioGroup *camera_group = glui->add_radiogroup_to_panel(camera_panel);
    GLUI_RadioButton *air_radio = glui->add_radiobutton_to_group(camera_group, "Aerea");
    GLUI_RadioButton *static_radio = glui->add_radiobutton_to_group(camera_group, "Estatica");
    GLUI_RadioButton *follow_radio = glui->add_radiobutton_to_group(camera_group, "Seguimiento coche 1");
    GLUI_RadioButton *follow2_radio = glui->add_radiobutton_to_group(camera_group, "Seguimiento coche 2");

    new GLUI_StaticText(glui, "");
    /*** Sombreado***/
    GLUI_Panel *shadowing_panel = new GLUI_Rollout(glui, "Sombreado", false);
    GLUI_RadioGroup *shadowing_group = glui->add_radiogroup_to_panel(shadowing_panel, &escena.shadowing, SHADOWING_ID, controlCallback);
    GLUI_RadioButton *sharp_radio = glui->add_radiobutton_to_group(shadowing_group, "Plano");
    GLUI_RadioButton *soft_radio = glui->add_radiobutton_to_group(shadowing_group, "Suavizado");


    /******** A�ade controles para las luces ********/


    // A�ade una separaci�n
    new GLUI_StaticText(glui, "");

    GLUI_Rollout *roll_lights = new GLUI_Rollout(glui, "Luces", false);

    GLUI_Panel *light0 = new GLUI_Panel(roll_lights, "Luz 1");
    GLUI_Panel *light1 = new GLUI_Panel(roll_lights, "Luz 2");

    new GLUI_Checkbox(light0, "Encendida", &light0_enabled, LIGHT0_ENABLED_ID, controlCallback);
    light0_spinner = new GLUI_Spinner(light0, "Intensidad:", &light0_intensity,
            LIGHT0_INTENSITY_ID, controlCallback);
    light0_spinner->set_float_limits(0.0, 1.0);
    GLUI_Scrollbar *sb;
    sb = new GLUI_Scrollbar(light0, "Rojo", GLUI_SCROLL_HORIZONTAL,
            &escena.light0_diffuse[0], LIGHT0_INTENSITY_ID, controlCallback);
    sb->set_float_limits(0, 1);
    sb = new GLUI_Scrollbar(light0, "Verde", GLUI_SCROLL_HORIZONTAL,
            &escena.light0_diffuse[1], LIGHT0_INTENSITY_ID, controlCallback);
    sb->set_float_limits(0, 1);
    sb = new GLUI_Scrollbar(light0, "Azul", GLUI_SCROLL_HORIZONTAL,
            &escena.light0_diffuse[2], LIGHT0_INTENSITY_ID, controlCallback);
    sb->set_float_limits(0, 1);

    new GLUI_Checkbox(light1, "Encendida", &light1_enabled, LIGHT1_ENABLED_ID, controlCallback);
    light1_spinner = new GLUI_Spinner(light1, "Intensidad:", &light1_intensity,
            LIGHT1_INTENSITY_ID, controlCallback);
    light1_spinner->set_float_limits(0.0, 1.0);
    sb = new GLUI_Scrollbar(light1, "Rojo", GLUI_SCROLL_HORIZONTAL,
            &escena.light1_diffuse[0], LIGHT1_INTENSITY_ID, controlCallback);
    sb->set_float_limits(0, 1);
    sb = new GLUI_Scrollbar(light1, "Verde", GLUI_SCROLL_HORIZONTAL,
            &escena.light1_diffuse[1], LIGHT1_INTENSITY_ID, controlCallback);
    sb->set_float_limits(0, 1);
    sb = new GLUI_Scrollbar(light1, "Azul", GLUI_SCROLL_HORIZONTAL,
            &escena.light1_diffuse[2], LIGHT1_INTENSITY_ID, controlCallback);
    sb->set_float_limits(0, 1);


    // A�ade una separaci�n
    new GLUI_StaticText(glui, "");

    /***  Rollout de Opciones ***/
    GLUI_Rollout *options = new GLUI_Rollout(glui, "Opciones", false);
    new GLUI_Checkbox(options, "Dibujar Coche", &escena.show_car);
    new GLUI_Checkbox(options, "Dibujar Ruedas", &escena.show_wheels);
    new GLUI_Checkbox(options, "Dibujar Carretera", &escena.show_road);


    /*** Disable/Enable botones ***/
    // A�ade una separaci�n
    new GLUI_StaticText(glui, "");
    new GLUI_Checkbox(glui, "Bloquear Movimiento", &enable_panel2);
    // A�ade una separaci�n
    new GLUI_StaticText(glui, "");
    new GLUI_Button(glui, "Resetear Posicion", RESET_ID, controlCallback);

    // A�ade una separaci�n
    new GLUI_StaticText(glui, "");

    /****** A 'quit' button *****/
    new GLUI_Button(glui, "Salir", 0, (GLUI_Update_CB) exit);

    // A�ade una separaci�n
    new GLUI_StaticText(glui, "");

    new GLUI_StaticText(glui, "Autor: Juan Puchol (C) 2012");
    new GLUI_StaticText(glui, "Alumno: Jorge Torregrosa Lloret 2013");
    // A�ade una separaci�n
    new GLUI_StaticText(glui, "");

    // A�ade un panel con texto con el valor de la selecci�n
    GLUI_Panel *panel0 = new GLUI_Panel(glui, "Seleccion");
    sel_tex = new GLUI_StaticText(panel0, "0");


    // Crea la subventana inferior
    glui2 = GLUI_Master.create_glui_subwindow(window_id, GLUI_SUBWINDOW_BOTTOM);

    /**** Link windows to GLUI, and register idle callback ******/
    glui->set_main_gfx_window(window_id);
    glui2->set_main_gfx_window(window_id);

    view_rot = new GLUI_Rotation(glui2, "Rotacion Escena", escena.view_rotate);
    view_rot->set_spin(1.0);
    new GLUI_Column(glui2, false);
    GLUI_Translation *trans_xy = new GLUI_Translation(glui2, "Traslacion Escena XY", GLUI_TRANSLATION_XY, escena.view_position);
    trans_xy->set_speed(.005);
    new GLUI_Column(glui2, false);
    GLUI_Translation *trans_x = new GLUI_Translation(glui2, "Traslacion Escena X", GLUI_TRANSLATION_X, escena.view_position);
    trans_x->set_speed(.005);
    new GLUI_Column(glui2, false);
    GLUI_Translation *trans_y = new GLUI_Translation(glui2, "Traslacion Escena Y", GLUI_TRANSLATION_Y, &escena.view_position[1]);
    trans_y->set_speed(.005);
    new GLUI_Column(glui2, false);
    GLUI_Translation *trans_z = new GLUI_Translation(glui2, "Traslacion Escena Z", GLUI_TRANSLATION_Z, &escena.scale);
    trans_z->set_speed(.005);

}

/**************************************** TGui::ControlCallback() *******************/

void __fastcall TGui::ControlCallback(int control) {
    if (control == LIGHT0_ENABLED_ID) {
        if (light0_enabled) {
            glEnable(GL_LIGHT0);
            light0_spinner->enable();
        } else {
            glDisable(GL_LIGHT0);
            light0_spinner->disable();
        }
    } else if (control == LIGHT1_ENABLED_ID) {
        if (light1_enabled) {
            glEnable(GL_LIGHT1);
            light1_spinner->enable();
        } else {
            glDisable(GL_LIGHT1);
            light1_spinner->disable();
        }
    } else if (control == LIGHT0_INTENSITY_ID) {
        float v[] = {
            escena.light0_diffuse[0], escena.light0_diffuse[1],
            escena.light0_diffuse[2], escena.light0_diffuse[3]
        };

        v[0] *= light0_intensity;
        v[1] *= light0_intensity;
        v[2] *= light0_intensity;

        glLightfv(GL_LIGHT0, GL_DIFFUSE, v);
    } else if (control == LIGHT1_INTENSITY_ID) {
        float v[] = {
            escena.light1_diffuse[0], escena.light1_diffuse[1],
            escena.light1_diffuse[2], escena.light1_diffuse[3]
        };

        v[0] *= light1_intensity;
        v[1] *= light1_intensity;
        v[2] *= light1_intensity;

        glLightfv(GL_LIGHT1, GL_DIFFUSE, v);
    } else if (control == ENABLE_ID) {
        glui2->enable();
    } else if (control == DISABLE_ID) {
        glui2->disable();
    } else if (control == RESET_ID) {
        memcpy(escena.view_position, view_position_c, 3 * sizeof (float));
        //memcpy(escena.view_rotate,view_rotate_c,16*sizeof(float));
        view_rot->reset();
        escena.scale = 1.0;
    } else if (control == PROJECTION_ID) {
        int tx, ty, tw, th;
        GLUI_Master.get_viewport_area(&tx, &ty, &tw, &th);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        switch (escena.projection) {
            case PERSPECTIVE_PROJ:
            {
                gluPerspective(45, escena.xy_aspect, 1.0, 1000.0);
                break;
            }
            case ORTHOGRAPHIC_PROJ:
            {
                glOrtho(-4 * escena.xy_aspect, 4 * escena.xy_aspect, -4, 4, -1000, 1000);
                break;
            }
            glMatrixMode(GL_MODELVIEW);
        }
    } else if (WIREFRAME_ID) {
        if (escena.wireframe)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    } else if (SHADOWING_ID) {
        if (escena.shadowing)
            glShadeModel(GL_SMOOTH);
        else
            glShadeModel(GL_FLAT);
    }

}

/***************************************** TGui::Idle() ***********/

void __fastcall TGui::Idle(void) {
    /* According to the GLUT specification, the current window is
       undefined during an idle callback.  So we need to explicitly change
       it if necessary */
    if (glutGetWindow() != window_id)
        glutSetWindow(window_id);

    /*  GLUI_Master.sync_live_all();  -- not needed - nothing to sync in this
                                         application  */

    if (enable_panel2)

        glui2->enable();
    else
        glui2->disable();

    glutPostRedisplay();
}

/**************************************** TGui::reshape() *************/

void __fastcall TGui::Reshape(int x, int y) {
    int tx, ty, tw, th;
    GLUI_Master.get_viewport_area(&tx, &ty, &tw, &th);
    glViewport(tx, ty, tw, th);

    escena.xy_aspect = (float) tw / (float) th;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, escena.xy_aspect, 1.0, 1000.0);

    glutPostRedisplay();
}

/***************************************** gui::motion() **********/

void __fastcall TGui::Motion(int x, int y) {
    if (escena.move_valid) {
        if (escena.mouse_b == 3) {
            if (escena.space_pressed) {
                if (escena.control_pressed) {
                    escena.view_position[2] -= 0.1*(escena.last_y - y);
                } else {
                    escena.view_position[0] -= 0.1*(escena.last_x - x);
                    escena.view_position[1] -= 0.1*(escena.last_y - y);
                }
            } else {
                float rot[16];
                glGetFloatv(GL_MODELVIEW_MATRIX, rot);
                glMatrixMode(GL_MODELVIEW);
                glPushMatrix();
                glLoadIdentity();
                if (escena.control_pressed) {
                    if (x >= escena.last_x)glRotated(x - escena.last_x * 0.01, 0, 0, 1);
                    else glRotated(escena.last_x - x * 0.01, 0, 0, 1);
                } else {
                    if (y >= escena.last_y)glRotated(y - escena.last_y * 0.01, 1, 0, 0);
                    else glRotated(escena.last_y - y * 0.01, 1, 0, 0);

                    if (x >= escena.last_x)glRotated(x - escena.last_x * 0.01, 0, 1, 0);
                    else glRotated(escena.last_x - x * 0.01, 0, 1, 0);
                }
                glGetFloatv(GL_MODELVIEW_MATRIX, rot);
                view_rot->set_float_array_val(rot);
                glPopMatrix();
            }
        } else if (escena.mouse_b == 1) {//ESCALADO (TRASLACION SOBRE EL EJE Z)
            int sx = 0;
            int sy = 0;
            int sz = 0;
            
            if (escena.control_pressed) {
                    sz = x - escena.last_x * 0.01;
                } else {
                    sx = x - escena.last_x * 0.01;
                    sy = y - escena.last_y * 0.01;
                }
                 int tx, ty, tw, th;
                 GLUI_Master.get_viewport_area(&tx, &ty, &tw, &th);
                 glMatrixMode(GL_PROJECTION);
                 glLoadIdentity();
                      gluPerspective (45+sx, escena.xy_aspect,1.0, 1000.0);
                 glMatrixMode(GL_MODELVIEW);
        }
    }
    escena.last_x = x;
    escena.last_y = y;

    glutPostRedisplay();
}

/***************************************** gui::Mouse() **********/

void __fastcall TGui::Mouse(int button, int button_state, int x, int y) {
    if (button_state == GLUT_DOWN) {//BOTON CLICKADO
        if (button == GLUT_LEFT_BUTTON)
            escena.mouse_b = 3; //ASIGNAMOS A LA VARIABLE EL VALOR 1
        else if (button == GLUT_MIDDLE_BUTTON)
            escena.mouse_b = 2; //ASIGNAMOS A LA VARIABLE EL VALOR 2
        else if (button == GLUT_RIGHT_BUTTON)
            escena.mouse_b = 1; //ASIGNAMOS A LA VARIABLE EL VALOR 3

    } else if (button_state == GLUT_UP) {//BOTON LEVANTADO
        escena.mouse_b = 0;
        if (button == GLUT_LEFT_BUTTON)//SELECCIONAREMOS EL OBJETO CUANDO LEVANTEMOS EL BOTON DEL RATON
            escena.Pick3D(x, y);

    }

    escena.move_valid = button_state == GLUT_DOWN;
}
