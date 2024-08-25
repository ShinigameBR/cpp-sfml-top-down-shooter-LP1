# Projeto de Jogo em C++ com SFML

Este projeto é um jogo de defesa de base desenvolvido em C++ utilizando a biblioteca SFML. O jogador controla uma base e deve defender contra ondas de inimigos, com a capacidade de se mover, atirar e coletar munição.

## Instruções de Compilação e Execução

1. **Certifique-se de que o SFML está instalado:**

   - No Arch, você pode instalar o SFML com:
     ```bash
     sudo pacman -S sfml
     ```
   - No Ubuntu, você pode instalar o SFML com:
     ```bash
     sudo apt-get install libsfml-dev
     ```

2. **Clone o repositório:**

   ```bash
   git clone https://github.com/ShinigameBR/cpp-sfml-top-down-shooter-LP1.git
   cd cpp-sfml-top-down-shooter-LP1
   ```

3. **Compile o projeto:**

   - Com o G++ execute (RECOMENDADO):

   ```bash
   g++ -g 'main.cpp' 'components/base.cpp' 'components/bullet.cpp' 'components/player.cpp' 'entities/ammo_box.cpp' 'entities/slow_enemy.cpp' 'entities/shooter_enemy.cpp' 'entities/agressive_enemy.cpp' 'entities/explosive_enemy.cpp' 'components/game.cpp' 'components/menu.cpp' -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -o 'main'
   ```

   - Com o Makefile execute:

   ```bash
   make
   ```

4. **Execute o jogo:**
   ```bash
   ./main
   ```

## Funcionalidades

### Funcionalidades Implementadas

- Movimentação do jogador com as teclas WASD.
- Movimento do jogador em direção ao mouse ao segurar com o botão direito.
- Ataque com tiros pelo jogador.
- Gerenciamento de munição e coleta de munição.
- Diferentes tipos de inimigos com comportamentos distintos.
- Interface de usuário para mostrar a saúde do jogador e da base.
- Exibição da quantidade de munição no jogador.

### Funcionalidades Não Implementadas

- Gráficos da nova geração.
- Implementação de fases diferentes.
- Sistema de pontuação.
- Músicas de fundo e efeitos sonoros adicionais.
- Salvamento e carregamento do progresso do jogo.

## Demonstração do Projeto

Você pode assistir a uma demonstração do projeto em funcionamento no vídeo abaixo:
https://youtu.be/okF8DtDFdzg