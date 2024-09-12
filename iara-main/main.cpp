#include <GL/glut.h>
#include <math.h>
//biblioteca para o som 
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>

// posição da sereia
float mermaidPosX = -0.8f;
float mermaidSpeedX = 0.01f;
float mermaidPosY = 0.4f;
float mermaidSpeedY = 0.0f;
float tailWave = 0.0f;
bool wireframe = false; // Alternar entre wireframe e sólido

// posição do barco
float boatPosX = 0.8f;   
float boatPosY = -0.8f;  
float boatWidth = 0.4f;
float boatHeight = 0.2f;


// Inicialização de SDL e musica
void PlaySound() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "Failed to initialize SDL_mixer: " << Mix_GetError() << std::endl;
        return;
    }
    
    Mix_Music* bgMusic = Mix_LoadMUS("audio/cantoDaSereia.mp3");
    if (!bgMusic) {
        std::cerr << "Failed to load music: " << Mix_GetError() << std::endl;
        return;
    }
    Mix_PlayMusic(bgMusic, -1);
}


// Rio com ondas verticais
void drawRiver() {
    glColor3f(0.0f, 0.0f, 0.8f); // agua
    glBegin(GL_QUADS);
        glVertex2f(-1.0f, -1.0f);
        glVertex2f(1.0f, -1.0f);
        glVertex2f(1.0f, 1.0f);
        glVertex2f(-1.0f, 1.0f);
    glEnd();

    // Desenhar ondas verticais
    glColor3f(0.0f, 0.5f, 1.0f); // ondas
    float waveFrequency = 10.0f;
    float waveAmplitude = 0.05f;
    for (int i = -10; i <= 10; i++) {
        float x = i * 0.2f;
        glBegin(GL_LINE_STRIP);
        for (int j = -100; j <= 100; j++) {
            float y = j * 0.01f;
            float wave = waveAmplitude * sinf(waveFrequency * y + tailWave);
            glVertex2f(x + wave, y);
        }
        glEnd();
    }
}

//Desenho da cabeça
void drawCircle(float x, float y, float radius) {
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 100; i++) {
        float angle = 2 * 3.1415926f * i / 100;
        float dx = radius * cosf(angle);
        float dy = radius * sinf(angle);
        glVertex2f(x + dx, y + dy);
    }
    glEnd();
}

//Desenhar a sereia 
void drawMermaid() {
    
    glColor3f(1.0f, 0.8f, 0.6f); // Cor da pele
    drawCircle(mermaidPosX, mermaidPosY + 0.4f, 0.05f);

    // Corpo 
    glBegin(GL_POLYGON);
        glColor3f(1.0f, 0.5f, 0.8f); // Cor 
        glVertex2f(mermaidPosX - 0.05f, mermaidPosY + 0.3f);
        glVertex2f(mermaidPosX + 0.05f, mermaidPosY + 0.3f);
        glVertex2f(mermaidPosX + 0.1f, mermaidPosY);
        glVertex2f(mermaidPosX - 0.1f, mermaidPosY);
    glEnd();

    // Braços 
    glBegin(GL_LINES);
        glColor3f(1.0f, 0.8f, 0.6f); // Cor 
        glVertex2f(mermaidPosX - 0.05f, mermaidPosY + 0.25f);
        glVertex2f(mermaidPosX - 0.15f, mermaidPosY + 0.15f);

        glVertex2f(mermaidPosX + 0.05f, mermaidPosY + 0.25f);
        glVertex2f(mermaidPosX + 0.15f, mermaidPosY + 0.15f);
    glEnd();

    // Cauda com movimento
    float tailMovement = 0.05f * sinf(tailWave);

    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.5f, 1.0f); // Cor 
        glVertex2f(mermaidPosX - 0.1f, mermaidPosY);
        glVertex2f(mermaidPosX + 0.1f, mermaidPosY);
        glVertex2f(mermaidPosX + tailMovement, mermaidPosY - 0.3f);
    glEnd();

    // Nadadeira da cauda com movimento
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.5f, 1.0f); // Cor 
        glVertex2f(mermaidPosX + tailMovement - 0.05f, mermaidPosY - 0.3f);
        glVertex2f(mermaidPosX + tailMovement + 0.05f, mermaidPosY - 0.3f);
        glVertex2f(mermaidPosX + tailMovement - 0.1f, mermaidPosY - 0.4f);

        glVertex2f(mermaidPosX + tailMovement + 0.05f, mermaidPosY - 0.3f);
        glVertex2f(mermaidPosX + tailMovement - 0.05f, mermaidPosY - 0.3f);
        glVertex2f(mermaidPosX + tailMovement + 0.1f, mermaidPosY - 0.4f);
    glEnd();
}

//barco
void drawBoat() {
    
    glColor3f(0.5f, 0.25f, 0.0f); 

    // Posicionar o barco no canto inferior direito
    float boatLeft = boatPosX - boatWidth / 2;
    float boatRight = boatPosX + boatWidth / 2;
    float boatTop = boatPosY + boatHeight;
    float boatBottom = boatPosY;

    glBegin(GL_POLYGON); // Corpo do barco
        glVertex2f(boatLeft, boatBottom);
        glVertex2f(boatRight, boatBottom);
        glVertex2f(boatRight - boatWidth / 4, boatTop);
        glVertex2f(boatLeft + boatWidth / 4, boatTop);
    glEnd();
}

//Colisão da sereia com as bordas
void checkCollision() {

    if (mermaidPosX > 1.0f || mermaidPosX < -1.0f) {
        mermaidSpeedX = -mermaidSpeedX;
    }
}

//Posição da sereia e o movimento da cauda
void update(int value) {
    // Mover a sereia
    mermaidPosX += mermaidSpeedX;
    mermaidPosY += mermaidSpeedY;

    // Verificar colisão com bordas
    checkCollision();

    // Atualizar a onda da cauda
    tailWave += 0.1f;    

    // Pedir para redesenhar a tela
    glutPostRedisplay();

    // Chamar essa função novamente após 16ms (~60fps)
    glutTimerFunc(16, update, 0);
}


//Desenhar na tela
void display() {
    // Limpar a tela
    glClear(GL_COLOR_BUFFER_BIT);
    //Rio com ondas
    drawRiver();
    //Sereia
    drawMermaid();
    //Barco
    drawBoat();
    // Trocar os buffers
    glutSwapBuffers();
}

// Gerenciar o modo wireframe ou sólido
void keyboard(unsigned char key, int x, int y) {
    if (key == 27)
        exit(0);
    if (key == 'w' || key == 'W')
        wireframe = !wireframe;
    if (wireframe)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Wireframe
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Sólido
}

// Função principal
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutCreateWindow("Iara");

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glutTimerFunc(16, update, 0);

    PlaySound();

    glutMainLoop();

    return 0;
}
