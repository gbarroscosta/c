#include <GL/glut.h>
#include <math.h>

// Variáveis de posição e direção da sereia
float mermaidPosX = 0.0f;
float mermaidSpeed = 0.01f;
float tailWave = 0.0f;

// Função para desenhar um círculo (usado para desenhar a cabeça)
void drawCircle(float x, float y, float radius) {
    glBegin(GL_TRIANGLE_FAN);
    int i;
    for (i = 0; i <= 100; i++) {
        float angle = 2 * 3.1415926f * i / 100;
        float dx = radius * cosf(angle);
        float dy = radius * sinf(angle);
        glVertex2f(x + dx, y + dy);
    }
    glEnd();
}

// Função para desenhar o fundo do rio com ondas verticais
void drawRiver() {
    glColor3f(0.0f, 0.0f, 0.8f); // Cor azul para a água
    glBegin(GL_QUADS);
        glVertex2f(-1.0f, -1.0f);
        glVertex2f(1.0f, -1.0f);
        glVertex2f(1.0f, 1.0f);
        glVertex2f(-1.0f, 1.0f);
    glEnd();

    // Desenhar ondas verticais
    glColor3f(0.0f, 0.5f, 1.0f); // Cor azul claro para as ondas
    float waveFrequency = 10.0f;
    float waveAmplitude = 0.05f;
    int i;
    for (i = -10; i <= 10; i++) {
        float x = i * 0.2f;
        glBegin(GL_LINE_STRIP);
        int j;
        for (j = -100; j <= 100; j++) {
            float y = j * 0.01f;
            float wave = waveAmplitude * sinf(waveFrequency * y + tailWave);
            glVertex2f(x + wave, y);
        }
        glEnd();
    }
}

// Função para desenhar a sereia humanizada
void drawMermaid() {
    // Cabeça da sereia
    glColor3f(1.0f, 0.8f, 0.6f); // Cor da pele
    drawCircle(mermaidPosX, 0.4f, 0.05f);

    // Corpo da sereia
    glBegin(GL_POLYGON);
        glColor3f(1.0f, 0.5f, 0.8f); // Cor do corpo
        glVertex2f(mermaidPosX - 0.05f, 0.3f);
        glVertex2f(mermaidPosX + 0.05f, 0.3f);
        glVertex2f(mermaidPosX + 0.1f, 0.0f);
        glVertex2f(mermaidPosX - 0.1f, 0.0f);
    glEnd();

    // Braços da sereia
    glBegin(GL_LINES);
        glColor3f(1.0f, 0.8f, 0.6f); // Cor da pele
        glVertex2f(mermaidPosX - 0.05f, 0.25f);
        glVertex2f(mermaidPosX - 0.15f, 0.15f);

        glVertex2f(mermaidPosX + 0.05f, 0.25f);
        glVertex2f(mermaidPosX + 0.15f, 0.15f);
    glEnd();

    // Cauda da sereia com movimento
    float tailMovement = 0.05f * sinf(tailWave);

    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.5f, 1.0f); // Cor da cauda
        glVertex2f(mermaidPosX - 0.1f, 0.0f);
        glVertex2f(mermaidPosX + 0.1f, 0.0f);
        glVertex2f(mermaidPosX + tailMovement, -0.3f);
    glEnd();

    // Nadadeira da cauda com movimento
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.5f, 1.0f); // Cor da nadadeira
        glVertex2f(mermaidPosX + tailMovement - 0.05f, -0.3f);
        glVertex2f(mermaidPosX + tailMovement + 0.05f, -0.3f);
        glVertex2f(mermaidPosX + tailMovement - 0.1f, -0.4f);

        glVertex2f(mermaidPosX + tailMovement + 0.05f, -0.3f);
        glVertex2f(mermaidPosX + tailMovement - 0.05f, -0.3f);
        glVertex2f(mermaidPosX + tailMovement + 0.1f, -0.4f);
    glEnd();
}

// Função para atualizar a posição da sereia e o movimento da cauda
void update(int value) {
    // Mover a sereia
    mermaidPosX += mermaidSpeed;

    // Verificar os limites da tela e inverter a direção
    if (mermaidPosX > 0.5f || mermaidPosX < -0.5f) {
        mermaidSpeed = -mermaidSpeed;
    }

    // Atualizar a onda da cauda
    tailWave += 0.1f;

    // Pedir para redesenhar a tela
    glutPostRedisplay();

    // Chamar essa função novamente após 16ms (~60fps)
    glutTimerFunc(20, update, 0);
}

// Função para desenhar na tela
void display() {
    // Limpar a tela
    glClear(GL_COLOR_BUFFER_BIT);

    // Desenhar o fundo do rio com ondas
    drawRiver();

    // Desenhar a sereia
    drawMermaid();

    // Trocar os buffers
    glutSwapBuffers();
}

// Função principal
int main(int argc, char** argv) {
    // Inicializar o GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    // Criar a janela
    glutCreateWindow("Sereia Nadando");

    // Definir a função de callback para desenho
    glutDisplayFunc(display);

    // Definir a cor de fundo
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Iniciar a atualização da posição da sereia e do movimento da cauda
    glutTimerFunc(16, update, 0);

    // Entrar no loop principal do GLUT
    glutMainLoop();

    return 0;
}

