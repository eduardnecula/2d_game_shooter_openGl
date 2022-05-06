#pragma once

#include "components/simple_scene.h"


namespace m1
{
    class Tema : public gfxc::SimpleScene
    {
     public:
        struct ViewportSpace
        {
            ViewportSpace() : x(0), y(0), width(1), height(1) {}
            ViewportSpace(int x, int y, int width, int height)
                : x(x), y(y), width(width), height(height) {}
            int x;
            int y;
            int width;
            int height;
        };

        struct LogicSpace
        {
            LogicSpace() : x(0), y(0), width(1), height(1) {}
            LogicSpace(float x, float y, float width, float height)
                : x(x), y(y), width(width), height(height) {}
            float x;
            float y;
            float width;
            float height;
        };

     public:
        Tema();
        ~Tema();
        

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void DrawScene(glm::mat3 visMatrix, float deltaTimeSeconds);

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;

        // Sets the logic space and view space
        // logicSpace: { x, y, width, height }
        // viewSpace: { x, y, width, height }
        glm::mat3 VisualizationTransf2D(const LogicSpace &logicSpace, const ViewportSpace &viewSpace);
        glm::mat3 VisualizationTransf2DUnif(const LogicSpace &logicSpace, const ViewportSpace &viewSpace);

        void SetViewportArea(const ViewportSpace &viewSpace, glm::vec3 colorColor = glm::vec3(0), bool clear = true);
        //  functie care face un inamic
        void draw_enemy(int nr);
        //  functie care trage cu proiectil
        void trageProiectil(float player_x, float player_y);
        void drawText(const std::string& text, const unsigned int x, const unsigned int y, const float r, const float g, const float b);
        //  pt vieti jucator
        void VietiJucator(glm::mat3 visMatrix);
        void TragProiectil(glm::mat3 visMatrix);
        void CollideWorld();

     protected:
        float lengthPlayer;  //  player
        ViewportSpace viewSpace;
        LogicSpace logicSpace;
        glm::mat3 modelMatrix, visMatrix;
        //  coordonate jucator
        float player_x = 0;
        float player_y = 0;
        float speed_player = 20;  //  viteza jucator
        bool trag = false;  //  daca trag cu proiectile
        float distanta_proiectil = 0;
        bool one_time = false;  //  pentru a pune jucatorul in centrul mapei

        //  mouse + rezolutie
        float mouse_x_proiec = 0;
        float mouse_y_proiec = 0;
        float rezolutie_x;
        float rezolutie_y;

        //  pentru a calcula panta pentru tragere cu proiectil
        float viteza_tragere = 0.5;
        
        //  inamici
        float inamic_x[10];
        float inamic_y[10];
        float speed_enemy = 0.03f;
        bool am_randat_enemy = false;
        bool stop_move = false;

        //  pentru a nr cadre
        float nr_cadre = 0;
        bool am_gasit_player = false;

        //  setare poz inamici initial
        bool setare_inamic_init = false;
        // nr inamici
        int nr_inamici = 4;
        //doar cand trag
        float trag_x = 0;
        float trag_y = 0;
        // vieti in joc
        int hearts = 4;
        // daca mor
        bool isDead = false;
        // cati mobi am omorat
        int deadMob = 0;
        
        // ca sa stiu cand am omorat toti inamicii
        int inamici_omorati = 0;

        // rotatia mouse-ului
        float angularStep = 0;
        float angularStep2 = 0;
        
        // marime patrat viata
        float lengthViata = 0;
    };
}   // namespace m1
