import pygame
import random
import sys

# Inicializar Pygame
pygame.init()

# Definir cores
PRETO = (0, 0, 0)
BRANCO = (255, 255, 255)
VERDE = (0, 255, 0)
VERMELHO = (255, 0, 0)

# Definir tamanho da tela e bloco
LARGURA = 640
ALTURA = 480
TAMANHO_BLOCO = 20

# Velocidade do jogo
FPS = 10

# Fonte para texto
fonte = pygame.font.SysFont(None, 35)

# Função para desenhar a cobra
def desenhar_cobra(cobra_corpo):
    for bloco in cobra_corpo:
        pygame.draw.rect(tela, VERDE, [bloco[0], bloco[1], TAMANHO_BLOCO, TAMANHO_BLOCO])

# Função para desenhar a comida
def desenhar_comida(comida_pos):
    pygame.draw.rect(tela, VERMELHO, [comida_pos[0], comida_pos[1], TAMANHO_BLOCO, TAMANHO_BLOCO])

# Função para mostrar pontuação
def mostrar_pontuacao(pontuacao):
    texto = fonte.render("Pontuação: " + str(pontuacao), True, BRANCO)
    tela.blit(texto, [10, 10])

# Função principal do jogo
def jogo():
    # Posição inicial da cobra
    cobra_x = LARGURA / 2
    cobra_y = ALTURA / 2
    cobra_corpo = [[cobra_x, cobra_y]]
    comprimento_cobra = 1

    # Direção inicial
    direcao = 'RIGHT'
    mudar_direcao = direcao

    # Posição da comida
    comida_x = round(random.randrange(0, LARGURA - TAMANHO_BLOCO) / 20.0) * 20.0
    comida_y = round(random.randrange(0, ALTURA - TAMANHO_BLOCO) / 20.0) * 20.0

    # Pontuação
    pontuacao = 0

    # Loop do jogo
    while True:
        for evento in pygame.event.get():
            if evento.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
            elif evento.type == pygame.KEYDOWN:
                if evento.key == pygame.K_LEFT and direcao != 'RIGHT':
                    mudar_direcao = 'LEFT'
                elif evento.key == pygame.K_RIGHT and direcao != 'LEFT':
                    mudar_direcao = 'RIGHT'
                elif evento.key == pygame.K_UP and direcao != 'DOWN':
                    mudar_direcao = 'UP'
                elif evento.key == pygame.K_DOWN and direcao != 'UP':
                    mudar_direcao = 'DOWN'

        # Atualizar direção
        direcao = mudar_direcao

        # Mover a cobra
        if direcao == 'LEFT':
            cobra_x -= TAMANHO_BLOCO
        elif direcao == 'RIGHT':
            cobra_x += TAMANHO_BLOCO
        elif direcao == 'UP':
            cobra_y -= TAMANHO_BLOCO
        elif direcao == 'DOWN':
            cobra_y += TAMANHO_BLOCO

        # Verificar colisão com as bordas
        if cobra_x < 0 or cobra_x >= LARGURA or cobra_y < 0 or cobra_y >= ALTURA:
            game_over(pontuacao)
            return

        # Adicionar nova posição à cobra
        cabeca_cobra = [cobra_x, cobra_y]
        cobra_corpo.append(cabeca_cobra)

        # Verificar se comeu a comida
        if cobra_x == comida_x and cobra_y == comida_y:
            comida_x = round(random.randrange(0, LARGURA - TAMANHO_BLOCO) / 20.0) * 20.0
            comida_y = round(random.randrange(0, ALTURA - TAMANHO_BLOCO) / 20.0) * 20.0
            comprimento_cobra += 1
            pontuacao += 1
        else:
            cobra_corpo.pop(0)

        # Verificar colisão com o próprio corpo
        for bloco in cobra_corpo[:-1]:
            if bloco == cabeca_cobra:
                game_over(pontuacao)
                return

        # Limpar tela
        tela.fill(PRETO)

        # Desenhar cobra e comida
        desenhar_cobra(cobra_corpo)
        desenhar_comida([comida_x, comida_y])

        # Mostrar pontuação
        mostrar_pontuacao(pontuacao)

        # Atualizar tela
        pygame.display.update()

        # Controlar velocidade
        relogio.tick(FPS)

# Função para mostrar mensagem de game over
def game_over(pontuacao):
    tela.fill(PRETO)
    texto = fonte.render("Game Over! Pontuação: " + str(pontuacao), True, BRANCO)
    tela.blit(texto, [LARGURA / 2 - 150, ALTURA / 2 - 50])
    texto2 = fonte.render("Pressione Q para sair ou C para jogar novamente", True, BRANCO)
    tela.blit(texto2, [LARGURA / 2 - 250, ALTURA / 2])
    pygame.display.update()

    while True:
        for evento in pygame.event.get():
            if evento.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
            elif evento.type == pygame.KEYDOWN:
                if evento.key == pygame.K_q:
                    pygame.quit()
                    sys.exit()
                elif evento.key == pygame.K_c:
                    jogo()

# Configurar tela
tela = pygame.display.set_mode((LARGURA, ALTURA))
pygame.display.set_caption("Jogo da Cobrinha")

# Relógio para controlar FPS
relogio = pygame.time.Clock()

# Iniciar jogo
jogo()
