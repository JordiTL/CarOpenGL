/****************************************************************************

    CarGL (main.cpp)

    Pr�ctica de Gr�ficos por Computador (Grado Ingenier�a Multimedia)
  -----------------------------------------------------------------------

    Noviembre 2012 (C) Juan Antonio Puchol Garc�a (puchol@dccia.ua.es)

    NOTA:   Para que esta aplicaci�n compile se necesita tener copiados los
            siguientes ficheros:

            Si es un Windows de 32 bits:
            libgui32.a -> C:\Program Files\CodeBlocks\MinGW\lib
            glut32.lib -> C:\Program Files\CodeBlocks\MinGW\lib

            Si es un Windows de 64 bits:
            libgui32.a -> C:\Program Files (x86)\CodeBlocks\MinGW\lib
            glut32.lib -> C:\Program Files (x86)\CodeBlocks\MinGW\lib

            glui.h     -> C:\Program Files (x86)\CodeBlocks\MinGW\include\GL
            glut.h     -> C:\Program Files (x86)\CodeBlocks\MinGW\include\GL

            glut32.dll -> C:\Windows\system

****************************************************************************/

#include "Objects.h"
#include <GL\glui.h>


// Otras Variables Globales

/**************************************** myGlutKeyboard() **********/

void Keyboard(unsigned char Key, int x, int y)
{
    switch(Key)
    {
        case 27:
        case 'q':
            exit(0);
            break;

    }

    glutPostRedisplay();
}

/**************************************** mySpecialKey() *************/

static void SpecialKey(int key, int x, int y)
{
    TPrimitiva *car = escena.GetCar(escena.seleccion);

    switch (key)
    {
        case GLUT_KEY_UP:   // El coche avanza
            car->rr+=8;
            car->tz += 0.05;
            break;
        case GLUT_KEY_DOWN:   // El coche retrocede
            car->rr-=8;
            car->tz -= 0.05;
            break;
    }

    glutPostRedisplay();
}

/***************************************** myGlutMenu() ***********/

void Menu( int value )
{
  Keyboard( value, 0, 0 );
}

void Mouse(int button, int button_state, int x, int y )
{
    gui.Mouse(button, button_state, x, y);
}

void Render()
{
    escena.Render();
}

void Idle()
{
    gui.Idle();
}

void Reshape(int x, int y){
    gui.Reshape(x, y);
}

void Motion(int x, int y){
    gui.Motion(x, y);
}




/**************************************** main() ********************/

int main(int argc, char* argv[])
{
    // Inicializa GLUT and crea la ventana principal
    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL | GLUT_MULTISAMPLE );
    glutInitWindowPosition( 50, 50 );
    glutInitWindowSize( 1000, 600 );

    int main_window = glutCreateWindow( "CarGL V1.1 (2012)" );

    // Inicializa los valores de OpenGL para esta Aplicaci�n
    escena.InitGL();
    gui.Init(main_window);

    glutDisplayFunc( Render );
    GLUI_Master.set_glutReshapeFunc( Reshape );
    GLUI_Master.set_glutKeyboardFunc( Keyboard );
    GLUI_Master.set_glutSpecialFunc( SpecialKey );
    GLUI_Master.set_glutMouseFunc( Mouse );
    glutMotionFunc( Motion );

    /**** We register the idle callback with GLUI, *not* with GLUT ****/
    GLUI_Master.set_glutIdleFunc( Idle );

    // Crea los objetos
    TPrimitiva *road = new TPrimitiva(CARRETERA_ID, CARRETERA_ID);
    TPrimitiva *car1 = new TPrimitiva(COCHE_ID*1, COCHE_ID);
    TPrimitiva *car2 = new TPrimitiva(COCHE_ID*2, COCHE_ID);
    TPrimitiva *semaforo1 = new TPrimitiva(SEMAFORO_ID, SEMAFORO_ID);
    TPrimitiva *rotonda1 = new TPrimitiva(ROTONDA_ID, ROTONDA_ID);
    TPrimitiva *acera1 = new TPrimitiva(ACERAS_ID, ACERAS_ID);
    TPrimitiva *reloj1 = new TPrimitiva(RELOJ_ID, RELOJ_ID);
    
    car1->colores[0][0] = 1.0;
    car1->colores[0][1] = 1.0;
    car1->colores[0][2] = 1.0;
    car1->colores[0][3] = 1.0;
    
    car1->colores[1][0] = 0.0;
    car1->colores[1][1] = 0.0;
    car1->colores[1][2] = 0.0;
    car1->colores[1][3] = 1.0;
    
    car1->colores[2][0] = 0.0;
    car1->colores[2][1] = 0.0;
    car1->colores[2][2] = 1.0;
    car1->colores[2][3] = 0.5;
    
    car1->colores[3][0] = 1.0;
    car1->colores[3][1] = 1.0;
    car1->colores[3][2] = 0.0;
    car1->colores[3][3] = 1.0;
    
    car1->colores[4][0] = 0.5;
    car1->colores[4][1] = 0.5;
    car1->colores[4][2] = 0.5;
    car1->colores[4][3] = 1.0;
    
    
    car1->tx = 2;
    car1->tz = -30;
    
    car2->colores[0][0] = 1.0;
    car2->colores[0][1] = 1.0;
    car2->colores[0][2] = 0.2;
    car2->colores[0][3] = 1.0;
    
    car2->colores[1][0] = 0.0;
    car2->colores[1][1] = 0.0;
    car2->colores[1][2] = 0.0;
    car2->colores[1][3] = 1.0;
    
    car2->colores[2][0] = 0.0;
    car2->colores[2][1] = 0.0;
    car2->colores[2][2] = 1.0;
    car2->colores[2][3] = 0.5;
    
    car2->colores[3][0] = 1.0;
    car2->colores[3][1] = 1.0;
    car2->colores[3][2] = 0.0;
    car2->colores[3][3] = 1.0;

    car2->colores[4][0] = 0.5;
    car2->colores[4][1] = 0.5;
    car2->colores[4][2] = 0.5;
    car2->colores[4][3] = 1.0;
    
    car2->tx = -2;
    car2->tz = -30;
    
    road->colores[0][0] = 0.0;
    road->colores[0][1] = 0.0;
    road->colores[0][2] = 0.0;
    road->colores[0][3] = 1.0;

    rotonda1->colores[0][0] = 0.0;
    rotonda1->colores[0][1] = 1.0;
    rotonda1->colores[0][2] = 0.0;
    rotonda1->colores[0][3] = 1.0;
    
    reloj1->colores[0][0] = 0.5;
    reloj1->colores[0][1] = 0.5;
    reloj1->colores[0][2] = 0.5;
    reloj1->colores[0][3] = 1.0;
    reloj1->ty = 2;
    
    acera1->colores[0][0] = 0.5;
    acera1->colores[0][1] = 0.5;
    acera1->colores[0][2] = 0.5;
    acera1->colores[0][3] = 1.0;
    
    escena.AddRoad(road);
    //escena.AddObject(semaforo1);
    escena.AddObject(rotonda1);
    escena.AddObject(acera1);
    escena.AddObject(reloj1);
    escena.AddCar(car1);
    escena.AddCar(car2);

    /**** Regular GLUT main loop ****/
    glutMainLoop();

    return EXIT_SUCCESS;
}

