#include "lab_m1/lab3/Tema.h"

#include <vector>
#include <iostream>
#include <math.h>

#include "lab_m1/lab3/transform2D.h"
#include "lab_m1/lab3/object2D.h"
#include "utils/glm_utils.h"


using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */
Tema::Tema()
{
}

Tema::~Tema()
{
}


void Tema::Init()
{   
    // rezolutie ecran
    glm::ivec2 resolution = window->GetResolution();
    rezolutie_x = (float) resolution.x;
    rezolutie_y = (float)resolution.y;

    viewSpace.x = 0;  // colt stg jos x
    viewSpace.y = 0;  // colt stg jos y
    viewSpace.width = resolution.x;
    viewSpace.height = resolution.y;

    logicSpace.x = 0;         // logic x
    logicSpace.y = 0;         // logic y
    logicSpace.width = 100;   // logic width
    logicSpace.height = 50;   // logic height
    
    auto camera = GetSceneCamera();
    camera->SetPosition(glm::vec3(rezolutie_x / 6, rezolutie_y /5, 50));  /// setare pozitie camera dar din view port; nu se seteaza cu coordonate logice
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();

    // astea sunt coordonate logice ale playerului
    glm::vec3 coorPlayer = glm::vec3(0, 0, 0);
    lengthPlayer = logicSpace.height / 12;  //  marime player
    // player, lungime, culoare, culoare plina
    Mesh* player = object2D::CreateSquare("player", coorPlayer, lengthPlayer, glm::vec3(0.75, 1, 0.18), true);

    glm::vec3 corner2 = glm::vec3(lengthPlayer, 0, 0);
    Mesh* eye1 = object2D::CreateSquare("eye1", corner2, lengthPlayer / 4, glm::vec3(0.84, 0.094, 0.184313), true);

    glm::vec3 corner3 = glm::vec3(lengthPlayer, lengthPlayer - lengthPlayer / 4, 0);
    Mesh* eye2 = object2D::CreateSquare("eye2", corner3, lengthPlayer / 4, glm::vec3(0.84, 0.094, 0.47), true);

    // obstacol 1
    float length = (float ) 0.4 * logicSpace.height;
    double r = 153 / 255;
    double g = 255 / 255;
    double b = 153 / 255;

    glm::vec3 corner4 = glm::vec3(lengthPlayer * 2, lengthPlayer * 2, 0);
    Mesh* obstacol1 = object2D::CreateSquare("obstacol1", corner4, length, glm::vec3(r, g, b), true);
    
    // obstacol 2
    length = (float) 0.3 * logicSpace.height;
    glm::vec3 corner5 = glm::vec3(logicSpace.width - length, 0, 0);
    Mesh* obstacol2 = object2D::CreateSquare("obstacol2", corner5, length, glm::vec3(0.2, 0.2, 0.2), true);
    
    // obstacol 3
    length = 0.15 * logicSpace.height;
    glm::vec3 corner6 = glm::vec3(0, logicSpace.height - length, 0);
    Mesh* obstacol3 = object2D::CreateSquare("obstacol3", corner6, length, glm::vec3(0.1, 0.1, 0.9), true);

    // obstacol 4
    length = 0.3 * logicSpace.height;
    glm::vec3 corner7 = glm::vec3(logicSpace.width / 2 + 0.2 * logicSpace.width, logicSpace.height * 0.2, 0);
    Mesh* obstacol4 = object2D::CreateSquare("obstacol4", corner7, length, glm::vec3(0.12, 0.67, 0.112), true);

    // proiectile
    glm::vec3 corner8 = glm::vec3(lengthPlayer, lengthPlayer / 2, 0);
    Mesh* proiectil = object2D::CreateSquare("proiectil", corner8, lengthPlayer / 4, glm::vec3(0, 0, 0), true);

    // healthbar
    // 4 patrate unul langa altul
    lengthViata = 0.02 * logicSpace.width;
    glm::vec3 corner9 = glm::vec3(0 , 0, 0);
    Mesh* health1 = object2D::CreateSquare("health1", corner9, lengthViata, glm::vec3(0.8, 0, 0), true);

    lengthViata = 0.02 * logicSpace.width;
    glm::vec3 corner10 = glm::vec3(0, 0, 0);
    Mesh* health2 = object2D::CreateSquare("health2", corner10, lengthViata, glm::vec3(0.85, 0, 0), true);

    lengthViata = 0.02 * logicSpace.width;
    glm::vec3 corner11 = glm::vec3(0, 0, 0);
    Mesh* health3 = object2D::CreateSquare("health4", corner11, lengthViata, glm::vec3(0.7, 0, 0), true);

    lengthViata = 0.02 * logicSpace.width;
    glm::vec3 corner12 = glm::vec3(0, 0, 0);
    Mesh* health4 = object2D::CreateSquare("health3", corner12, lengthViata, glm::vec3(0.75, 0, 0), true);

    // inamic
    glm::vec3 corner13 = glm::vec3(0, 0, 0);
    glm::vec3 corner14 = glm::vec3(0, -(lengthPlayer / 4), 0);
    glm::vec3 corner15 = glm::vec3(0 + 0.75 * lengthPlayer, -(lengthPlayer / 4), 0);
    Mesh* inamic = object2D::CreateSquare("inamic", corner13, lengthPlayer, glm::vec3(0.1, 0.1, 0.1), true);
    Mesh* inamic_eye1 = object2D::CreateSquare("inamic_eye1", corner14, lengthPlayer / 4, glm::vec3(0.2, 0, 0.1), true);
    Mesh* inamic_eye2 = object2D::CreateSquare("inamic_eye2", corner15, lengthPlayer / 4, glm::vec3(0.3, 0.2, 0.1), true);

    // pereti harta
    glm::vec3 corner16 = glm::vec3(logicSpace.width, 0, 0);
    Mesh* pereteDreapta = object2D::CreateSquare("pereteDreapta", corner16, 5 * logicSpace.height, glm::vec3(0, 0, 0), true);

    glm::vec3 corner17 = glm::vec3(-logicSpace.height, 0, 0);
    Mesh* pereteStanga = object2D::CreateSquare("pereteStanga", corner17, logicSpace.height, glm::vec3(0, 0, 0), true);

    glm::vec3 corner18 = glm::vec3(0, logicSpace.height, 0);
    Mesh* pereteSus = object2D::CreateSquare("pereteSus", corner18, 5 * logicSpace.width, glm::vec3(0, 0, 0), true);

    glm::vec3 corner19 = glm::vec3(0, -logicSpace.height, 0);
    Mesh* pereteJos = object2D::CreateSquare("pereteJos", corner19, logicSpace.width / 2, glm::vec3(0, 0, 0), true);

    glm::vec3 corner20 = glm::vec3(logicSpace.width / 2, -logicSpace.height, 0);
    Mesh* pereteJos2 = object2D::CreateSquare("pereteJos2", corner20, logicSpace.width / 2, glm::vec3(0, 0, 0), true);

    // player
    AddMeshToList(player);
    AddMeshToList(eye1);
    AddMeshToList(eye2);

    // obstacole
    AddMeshToList(obstacol1);
    AddMeshToList(obstacol2);
    AddMeshToList(obstacol3);
    AddMeshToList(obstacol4);

    // proiectil
    AddMeshToList(proiectil);

    // healthbar
    AddMeshToList(health1);
    AddMeshToList(health2);
    AddMeshToList(health3);
    AddMeshToList(health4);

    // inamic
    AddMeshToList(inamic);
    AddMeshToList(inamic_eye1);
    AddMeshToList(inamic_eye2);
 
    // pereti
    AddMeshToList(pereteDreapta);
    AddMeshToList(pereteStanga);
    AddMeshToList(pereteSus);
    AddMeshToList(pereteJos);
    AddMeshToList(pereteJos2);
}


// Uniform 2D visualization matrix (same scale factor on x and y axes)
glm::mat3 Tema::VisualizationTransf2DUnif(const LogicSpace & logicSpace, const ViewportSpace & viewSpace)
{
    float sx, sy, tx, ty, smin;
    sx = viewSpace.width / logicSpace.width;
    sy = viewSpace.height / logicSpace.height;
    if (sx < sy)
        smin = sx;
    else
        smin = sy;
    tx = viewSpace.x - smin * logicSpace.x + (viewSpace.width - smin * logicSpace.width) / 2;
    ty = viewSpace.y - smin * logicSpace.y + (viewSpace.height - smin * logicSpace.height) / 2;

    return glm::transpose(glm::mat3(
        smin, 0.0f, tx,
        0.0f, smin, ty,
        0.0f, 0.0f, 1.0f));
}


void Tema::SetViewportArea(const ViewportSpace & viewSpace, glm::vec3 colorColor, bool clear)
{
    glViewport(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);
    //cout << "viewspace.x | viewspace.y" << endl << a << " | " << b << endl;
    glEnable(GL_SCISSOR_TEST);
    glScissor(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(colorColor.r, colorColor.g, colorColor.b, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);
    /**/
    GetSceneCamera()->SetOrthographic(
        (float)viewSpace.x,
        (float)(viewSpace.x + viewSpace.width),
        (float)viewSpace.y,
        (float)(viewSpace.y + viewSpace.height),
        0.1f,
        400);

    GetSceneCamera()->Update();
}


void Tema::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}


void Tema::Update(float deltaTimeSeconds){

    if (isDead) {
        glm::ivec2 resolution = window->GetResolution();
        // ce o sa vad eu la ecran, daca mor
        viewSpace = ViewportSpace(0, 0, resolution.x, resolution.y);
        // setare culoare + lumea viewSpace
        SetViewportArea(viewSpace, glm::vec3(0.5, 0.5, 1), true);
    }
    else {
        glm::ivec2 resolution = window->GetResolution();
        //toata mapa principala
        // ce o sa vad eu la ecran
        viewSpace = ViewportSpace(0, 0, 2 * resolution.x, 2 * resolution.y);
        SetViewportArea(viewSpace, glm::vec3(1, 0.3, 0), true);
        visMatrix = glm::mat3(1);
        visMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);
        DrawScene(visMatrix, deltaTimeSeconds);

        // MINI MAP
        viewSpace = ViewportSpace(resolution.x * 0.80, 0, resolution.x / 6, resolution.y / 5);
        SetViewportArea(viewSpace, glm::vec3(0.5f), true);
        visMatrix = glm::mat3(1);
        visMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);
        DrawScene(visMatrix, deltaTimeSeconds);
    }
}


void Tema::FrameEnd()
{
}


//  o functie care sa urmareasca un player
//  si sa deseze inamicul spre player
void Tema::draw_enemy(int nr) {
    // vreau sa ma urmareasca inamicul
    float startPointX = inamic_x[nr];
    float endPointY = inamic_y[nr];

    // trebuie sa ajung la acest punct in spatiu
    float pointX = player_x;
    float pointY = player_y;

    float speed = 0.08 + (rand() % 3) / 50;
    
    float panta = 0;
    if ((pointX - startPointX) != 0) {

        panta = (pointY - endPointY) / (pointX - startPointX);
        // ca sa nu se deplaseze brusc repede
        if (panta > 0 && panta < 1) {
            panta = 1;
        }
        if (panta > -1 && panta < 0) {
            panta = -1;
        }
        if (panta > 2) {
            panta = 2;
        }
        else if (panta < -2) {
            panta = -2;
        }
    }
    else {
        am_gasit_player = true;
    }

    if (player_x > inamic_x[nr] && !am_gasit_player) {
        inamic_x[nr] += speed;
    }
    else if (!am_gasit_player) {
        inamic_x[nr] -= speed;
    }
    if (panta != 0) {
        inamic_y[nr] = panta * (inamic_x[nr] - startPointX) + endPointY;
    }

    else {
        if (player_y > inamic_y[nr]) {
            inamic_y[nr] += speed;
        }
        else {
            inamic_y[nr] -= speed;
        }
    }

    modelMatrix = visMatrix * transform2D::Translate(inamic_x[nr], inamic_y[nr]);
    RenderMesh2D(meshes["inamic_eye1"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["inamic_eye2"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["inamic"], shaders["VertexColor"], modelMatrix);
}


//  functie care sa afize vietile jucatorului
void Tema::VietiJucator(glm::mat3 visMatrix)
{
    // health bar
    float distance_up = 0.15;
    if (hearts == 4) {
        modelMatrix = visMatrix * transform2D::Translate(player_x + distance_up * logicSpace.width, player_y + distance_up * logicSpace.height);
        RenderMesh2D(meshes["health1"], shaders["VertexColor"], modelMatrix);

        modelMatrix = visMatrix * transform2D::Translate(player_x + distance_up * logicSpace.width +
            lengthViata, player_y + distance_up * logicSpace.height);
        RenderMesh2D(meshes["health2"], shaders["VertexColor"], modelMatrix);

        modelMatrix = visMatrix * transform2D::Translate(player_x + distance_up * logicSpace.width +
            (2 * lengthViata), player_y + distance_up * logicSpace.height);
        RenderMesh2D(meshes["health3"], shaders["VertexColor"], modelMatrix);

        modelMatrix = visMatrix * transform2D::Translate(player_x + distance_up * logicSpace.width +
            (3 * lengthViata), player_y + distance_up * logicSpace.height);
        RenderMesh2D(meshes["health4"], shaders["VertexColor"], modelMatrix);
    }
    else if (hearts == 3) {
        modelMatrix = visMatrix * transform2D::Translate(player_x + distance_up * logicSpace.width, player_y + distance_up * logicSpace.height);
        RenderMesh2D(meshes["health1"], shaders["VertexColor"], modelMatrix);

        modelMatrix = visMatrix * transform2D::Translate(player_x + distance_up * logicSpace.width +
            lengthViata, player_y + distance_up * logicSpace.height);
        RenderMesh2D(meshes["health2"], shaders["VertexColor"], modelMatrix);

        modelMatrix = visMatrix * transform2D::Translate(player_x + distance_up * logicSpace.width +
            (2 * lengthViata), player_y + distance_up * logicSpace.height);
        RenderMesh2D(meshes["health3"], shaders["VertexColor"], modelMatrix);
    }
    else if (hearts == 2) {
        modelMatrix = visMatrix * transform2D::Translate(player_x + distance_up * logicSpace.width, player_y + distance_up * logicSpace.height);
        RenderMesh2D(meshes["health1"], shaders["VertexColor"], modelMatrix);

        modelMatrix = visMatrix * transform2D::Translate(player_x + distance_up * logicSpace.width +
            lengthViata, player_y + distance_up * logicSpace.height);
        RenderMesh2D(meshes["health2"], shaders["VertexColor"], modelMatrix);
    }
    else if (hearts == 1) {
        modelMatrix = visMatrix * transform2D::Translate(player_x + distance_up * logicSpace.width, player_y + distance_up * logicSpace.height);
        RenderMesh2D(meshes["health1"], shaders["VertexColor"], modelMatrix);
    }
}


//  functie pentru ca playerul sa traga cu proiectile
void Tema::TragProiectil(glm::mat3 visMatrix) {
    // daca trag cu proiectile
    if (trag == true && distanta_proiectil < 400) {
        // plec de la punctul meu
        // coordonate logice
        float startPointX = player_x;
        float endPointY = player_y;
        // trebuie sa ajung la acest punct in spatiu
        float pointX = mouse_x_proiec * (logicSpace.width / rezolutie_x);
        float pointY = (rezolutie_y - mouse_y_proiec) * (logicSpace.height / rezolutie_y);

        float panta = 0;
        if ((pointX - startPointX) != 0) {
            panta = (pointY - endPointY) / (pointX - startPointX);
        }
        if (pointX > trag_x) {
            trag_x += viteza_tragere;
        }
        else {
            trag_x -= viteza_tragere;
        }
        trag_y = panta * (trag_x - startPointX) + endPointY;

        modelMatrix = visMatrix * transform2D::Translate(trag_x, trag_y) * transform2D::Rotate(angularStep2);
        RenderMesh2D(meshes["proiectil"], shaders["VertexColor"], modelMatrix);
        distanta_proiectil++;
    }
    else {
        trag = false;
        distanta_proiectil = 0;
    }
}


// daca player-ul se loveste de obiecte
void Tema::CollideWorld()
{
    // daca lovesc un inamic cu un proiectil
    for (int i = 0; i < nr_inamici; i++) {
        bool collisionX = trag_x + lengthPlayer / 2 >= inamic_x[i] &&
            inamic_x[i] + lengthPlayer >= trag_x;
        // collision y-axis?
        bool collisionY = trag_y + lengthPlayer / 2 >= inamic_y[i] &&
            inamic_y[i] + lengthPlayer >= trag_y;

        if (collisionX == true && collisionY == true) {
            // pun -1000 pe inamic, iar asta inseamna ca este dezactivat
            inamic_x[i] = -1000;
            inamic_y[i] = -1000;
            inamici_omorati++;
            trag = false;
            distanta_proiectil = 0;
            deadMob++; // incrementez si afizez cati monstri am omorat
        }
    }

    // daca ma loveste un inamic pe mine
    for (int i = 0; i < nr_inamici; i++) {
        bool collisionX = player_x + lengthPlayer >= inamic_x[i] &&
            inamic_x[i] + lengthPlayer >= player_x;
        // collision y-axis?
        bool collisionY = player_y + lengthPlayer >= inamic_y[i] &&
            inamic_y[i] + lengthPlayer >= player_y;

        if (collisionX == true && collisionY == true) {
            // pun -1000 pe inamic, iar asta inseamna ca este dezactivat
            inamic_x[i] = -1000;
            inamic_y[i] = -1000;
            inamici_omorati++;
            cout << "Inamici omorati: " << inamici_omorati << endl << endl;
            hearts--;
            if (hearts == 0)
                isDead = true;
        }
    }
}


void Tema::DrawScene(glm::mat3 visMatrix, float deltaTimeSeconds)
{
    // viata jucator
    VietiJucator(visMatrix);

    if (one_time == false) {
        // pun jucatorul in centru
        player_x += logicSpace.width / 4;
        player_y += logicSpace.height / 4;
        one_time = true;
    }

    // inamici pusi la pozitii random
    if (setare_inamic_init == false) {
        for (int i = 0; i < nr_inamici; i++) {
            // un inamic de colt dreapta sus
            int aux = rand() % 10; // interval 0 - 10
            if (i == 0) { // de sus
                inamic_x[i] = 0 + aux * (logicSpace.width / 10);
                inamic_y[i] = 0;
            } else if (i == 1) { // de jos
                inamic_x[i] = 0 + aux * (logicSpace.width / 10);
                inamic_y[i] = logicSpace.height;
            } else if (i == 2) { // din stanga
                inamic_x[i] = 0;
                inamic_y[i] = 0 + aux * (logicSpace.height / 5);
            } else if (i == 3) { // din dreapta
                inamic_x[i] = logicSpace.width;
                inamic_y[i] = 0 + aux * (logicSpace.height / 5);
            }
        }
        setare_inamic_init = true;
    }

    // desenez fiecare inamic
    for (int i = 0; i < nr_inamici; i++) {
        if (inamic_x[i] != -1000 && inamic_y[i] != -1000) {
            draw_enemy(i);
        }
    }

    //  trag cu proiectile
    TragProiectil(visMatrix);

    //  daca ma lovesc de lucruri
    CollideWorld();

    if (inamici_omorati == nr_inamici) {
        setare_inamic_init = false;
        inamici_omorati = 0;
    }

    //  aici desenez jucatorul 
    // este format din 2 ochi si corp 
    modelMatrix = visMatrix * transform2D::Translate(player_x, player_y);
    modelMatrix *= transform2D::Rotate(angularStep);
    RenderMesh2D(meshes["eye1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix * transform2D::Translate(player_x, player_y) * transform2D::Rotate(angularStep);
    RenderMesh2D(meshes["eye2"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix * transform2D::Translate(player_x, player_y) * transform2D::Rotate(angularStep);
    RenderMesh2D(meshes["player"], shaders["VertexColor"], modelMatrix);

    //  obstacole
    modelMatrix = visMatrix * transform2D::Translate(0, 0);
    RenderMesh2D(meshes["obstacol1"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["obstacol2"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["obstacol3"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["obstacol4"], shaders["VertexColor"], modelMatrix);

    // pereti harta
    RenderMesh2D(meshes["pereteStanga"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["pereteDreapta"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["pereteSus"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["pereteJos"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["pereteJos2"], shaders["VertexColor"], modelMatrix);
}


//  daca ma misc cu tastatura
void Tema::OnInputUpdate(float deltaTime, int mods)
{
    auto camera = GetSceneCamera();

    if (window->KeyHold(GLFW_KEY_W)) {
        if (0.9 * logicSpace.height >= player_y) {
            //  player sus
            player_y += speed_player * deltaTime;
            logicSpace.y += speed_player * deltaTime;
        }
    }

    if (window->KeyHold(GLFW_KEY_A)) {
        if (0.1 * logicSpace.width <= player_x) {
            // player stanga
            player_x -= speed_player * deltaTime;
            logicSpace.x -= speed_player * deltaTime;
        }
    }

    if (window->KeyHold(GLFW_KEY_S)) {
        if (0.1 * logicSpace.height <= player_y) {
            //  player jos
            player_y -= speed_player * deltaTime;
            logicSpace.y -= speed_player * deltaTime;
        }
    }

    if (window->KeyHold(GLFW_KEY_D)) {
        if (0.9 * logicSpace.width >= player_x) {
            //  player dreapta
            player_x += speed_player * deltaTime;
            logicSpace.x += speed_player * deltaTime;
        }
    }

    // in functie de cum ma misc, schimb si pozitia player-ului
    camera->SetPosition(glm::vec3(player_x, player_y, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
}


void Tema::OnKeyPress(int key, int mods)
{
}


void Tema::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


//  daca misc mouse-ul
void Tema::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    float width = viewSpace.width;
    float height = viewSpace.height;
    angularStep =
        atan2f((height - mouseY * height / rezolutie_y - height / 2),
        (mouseX * width / rezolutie_x - width / 2));
}


// daca trag cu mouse-ul
void Tema::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    float width = viewSpace.width;
    float height = viewSpace.height;
    angularStep2 =
        atan2f((height - mouseY * height / rezolutie_y - height / 2),
            (mouseX * width / rezolutie_x - width / 2));
    if (button == 1) {
        trag = true;
        mouse_x_proiec = mouseX;
        mouse_y_proiec = mouseY;
        trag_x = player_x;
        trag_y = player_y;
    }
}


void Tema::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
}


void Tema::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}
