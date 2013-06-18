
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


#define COCHE_ID	    100 // Un coche cada 100

#define COCHE           0
#define RUEDA	        10
#define MARCADOR        20
#define CHAPA           30     
#define CRISTAL         40
#define PLASTICOS       50
#define LUCES           60
// etc...

// IDs para los callbacks de TGui
#define LIGHT0_ENABLED_ID    200
#define LIGHT1_ENABLED_ID    201
#define LIGHT0_INTENSITY_ID  250
#define LIGHT1_INTENSITY_ID  260

#define ENABLE_ID            300
#define DISABLE_ID           301

#define RESET_ID             400

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
    
    GLuint stoneTexture;
    GLuint grassTexture;
    GLuint streetTexture;
    
    float xy_aspect;
    int last_x, last_y;

    // live variables usadas por GLUI en TGui
    int wireframe;
    int z_buffer;
    int culling;
    float scale;

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
    GLuint LoadTextureJPEG( char * filename, int wrap, int width, int height);
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
    GLUI_RadioGroup *radio;
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
