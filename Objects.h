
/****************************************************************************

    CarGL (Objects.h)

    Pr�ctica de Gr�ficos por Computador (Grado Ingenier�a Multimedia)
  -----------------------------------------------------------------------

    Noviembre 2012 (C) Juan Antonio Puchol Garc�a (puchol@dccia.ua.es)

 ****************************************************************************/

//---------------------------------------------------------------------------
#ifndef ObjectsH
#define ObjectsH
//---------------------------------------------------------------------------

#include <GL/glui.h>

// Identificadores internos de los objetos
#define CARRETERA_ID    10
#define SEMAFORO_ID     20
#define ROTONDA_ID      30
#define ACERAS_ID       31
#define RELOJ_ID        40
#define BANCO_ID        45
#define DAVID_ID        48
#define COMISARIA_ID    50
#define FAROLA_ID       55
#define VEGETACION_ID   60 
#define STOP_ID   65
#define PARQUE_ID       70
#define VIVIENDAS_ID    80

#define COCHE_ID	    100 // Un coche cada 100

//CARRETERA
#define CALZADA 0
#define LINEAS  1
// COCHE
#define COCHE           0
#define RUEDA	        1
#define MARCADOR        2
#define CHAPA           3     
#define CRISTAL         4
#define PLASTICOS       5
#define LUCES           6

//COMISARIA
#define COM_BLOQUES         1
#define COM_CRISTAL         2
#define COM_PUERTA          3
#define COM_COLUMNAS        4

//VEGETACION
#define HOJAS           1
#define TRONCO          2

//PARQUE
#define P_SUELO         1
#define P_AGUA          2
#define P_PUENTE        3

//VIVIENDAS
#define VIV_BLOQUES         1
#define VIV_CRISTAL         2
#define VIV_PUERTA          3

//BANCO
#define BASE          1
#define ASIENTO       2

//DAVID
#define PEDESTAL        0
#define FIGURA          1

//STOP
#define S_BASE 0
#define S_SIGNAL 1
// etc...

// IDs para los callbacks de TGui
#define LIGHT0_ENABLED_ID    200
#define LIGHT1_ENABLED_ID    201
#define LIGHT0_INTENSITY_ID  250
#define LIGHT1_INTENSITY_ID  260

#define ENABLE_ID            300
#define DISABLE_ID           301

#define RESET_ID             400
#define PROJECTION_ID        500
#define WIREFRAME_ID         510
#define ZBUFFER_ID           520
#define SHADOWING_ID         530
#define PERSPECTIVE_PROJ        0
#define ORTHOGRAPHIC_PROJ        1

//************************************************************** Clase TPrimtiva

class TPrimitiva {
public: // Atributos
    int ID; // DisplayLists del objeto
    int tipo; // Tipo de Objeto
    float tx, ty, tz; // Posici�n del objeto
    float sx, sy, sz; // Escalado del objeto
    float rx, ry, rz; // Rotaci�n del objeto
    float rr; // Rotaci�n de las ruedas
    float colores[5][4]; // Color RGB y canal Alfa

public: // M�todos
    TPrimitiva(int DL, int tipo);
    void __fastcall Render(int seleccion, bool reflejo = false);
};

//************************************************************** Clase TEscena

class TEscena {
public: // Atributos
    int seleccion; // Objeto seleccionado, 0=ninguno
    int num_objects; // N�mero de objetos (excepto coches)
    int num_cars; // N�mero de coches
    int num_roads; // N�mero de coches

    TPrimitiva *cars[10];
    TPrimitiva *objects[100];
    TPrimitiva *roads[10];

    int roadID;

    int show_car;
    int show_wheels;
    int show_road;
    int show_semaforo;
    int show_rotonda;
    int show_aceras;
    int show_reloj;
    int show_buildings;
    int show_vegetation;
    int show_park;
    int show_benchs;
    int show_david;
    int show_roadLines;
    int show_lampost;
    int show_stop;


    GLfloat view_position[3];
    GLfloat view_rotate[16];

    // Vectores de luces y materiales
    GLfloat light0_ambient[4];
    GLfloat light0_diffuse[4];
    GLfloat light0_specular[4];
    GLfloat light0_position[4];

    GLfloat light1_ambient[4];
    GLfloat light1_diffuse[4];
    GLfloat light1_specular[4];
    GLfloat light1_position[4];

    GLfloat mat_ambient[4];
    GLfloat mat_diffuse[4];
    GLfloat mat_specular[4];
    GLfloat high_shininess[1];
    
    GLfloat disable_light_ambient[4];

    GLuint stoneTexture;
    GLuint grassTexture;
    GLuint streetTexture;

    GLuint doorTexture;
    GLuint brickTexture;
    GLuint marbleTexture;

    GLuint leavesTexture;
    GLuint barkTexture;

    GLuint bridgeTexture;
    GLuint waterTexture;

    GLuint brick2Texture;
    GLuint door2Texture;

    GLuint stopTexture;
    
    float xy_aspect;
    int last_x, last_y;
    
    int mouse_b;
    int rrx,rry,rrz;
    
    // live variables usadas por GLUI en TGui
    int wireframe;
    int z_buffer;
    int culling;
    int projection;
    int ambientLights;
    int clockWiseFaces;
    int shadowing;
    
    float scale;
    
    int move_valid;
    int control_pressed;
    int space_pressed;

public: // M�todos
    TEscena();

    void __fastcall InitGL();
    void __fastcall Render();
    void __fastcall RenderCars(bool reflejo = false);
    void __fastcall RenderObjects(bool reflejo = false);
    void __fastcall RenderRoads(bool reflejo = false);

    void __fastcall AddCar(TPrimitiva *car);
    void __fastcall AddObject(TPrimitiva *object);
    void __fastcall AddRoad(TPrimitiva *object);

    TPrimitiva __fastcall *GetCar(int id);

    void __fastcall Pick3D(int mouse_x, int mouse_y);


};

//************************************************************** Clase TGui

class TGui {
public:
    int window_id;

    // live variables usadas por GLUI
    int enable_panel2;
    int light0_enabled;
    int light1_enabled;
    float light0_intensity;
    float light1_intensity;

    GLUI *glui, *glui2;
    GLUI_Spinner *light0_spinner;
    GLUI_Spinner *light1_spinner;
    GLUI_RadioGroup *vis_group;
    GLUI_Panel *obj_panel;
    GLUI_Rotation *view_rot;
    GLUI_StaticText *sel_tex;

public:
    TGui();
    void __fastcall Init(int main_window);
    void __fastcall ControlCallback(int control);
    void __fastcall Idle(void);
    void __fastcall Reshape(int x, int y);
    void __fastcall Motion(int x, int y);
    void __fastcall Mouse(int button, int button_state, int x, int y);
};

//************************************************************** Variables de clase

extern TEscena escena;
extern TGui gui;

#endif
