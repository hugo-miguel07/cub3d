# Drawmap e Raycasting (explicacao completa)

Este documento explica, com detalhe e linguagem simples, o caminho completo de `draw_map()` ate ao raycasting no teu projeto. A ideia e tu conseguires seguir cada passo como se estivesses a simular o processo na cabeca.

## Onde isto vive no codigo

- Renderizacao geral: [srcs/execution/drawer.c](srcs/execution/drawer.c)
- Mapa 3D (raycasting): [srcs/execution/drawmap.c](srcs/execution/drawmap.c)
- Raycasting base: [srcs/execution/raycasting.c](srcs/execution/raycasting.c)
- Utilitarios do DDA: [srcs/execution/raycasting_utils.c](srcs/execution/raycasting_utils.c)
- Texturas e pixeis: [srcs/execution/textures.c](srcs/execution/textures.c), [srcs/execution/drawer_utils.c](srcs/execution/drawer_utils.c)
- Estruturas: [includes/cub3d.h](includes/cub3d.h)

## Visao geral (uma frase)

Para cada coluna de pixeis do ecran, o motor manda um raio, encontra onde ele bate numa parede do mapa 2D, calcula a altura da parede no ecran e pinta essa coluna usando a textura correta.

## Visao geral (passo a passo simples)

1. Limpa o frame e desenha teto e chao.
2. Para cada `x` do ecran, cria um raio.
3. Anda com esse raio no grid do mapa ate bater numa parede.
4. Mede a distancia e decide a altura da parede no ecran.
5. Escolhe a textura correta (N/S/E/W) e pinta a coluna.
6. Guarda a distancia no `zbuffer`.

Isto repete para todas as colunas, criando a ilusao de 3D.

## As estruturas importantes (traducoes simples)

- `t_game`: o mundo todo (janela, frame, mapa, texturas, jogador).
- `t_player`: posicao do jogador (`px`, `py`) e direcao (`dirx`, `diry`).
- `t_rt_state`: o estado temporario de UM raio. Tudo o que e preciso para desenhar UMA coluna.
- `t_texture`: uma imagem de parede (pixels + tamanho).

Se quiseres ver os campos exatos, esta em [includes/cub3d.h](includes/cub3d.h).

## O pipeline real no codigo

A renderizacao chama `draw_scene()`:

```
render loop
  -> draw_scene()
       -> clean_buffer()
       -> draw_floor_ceiling()
       -> draw_map()
       -> draw_minimap()
```

A tua pergunta foca-se daqui para baixo: `draw_map()`.

## `draw_map()` - a maquina de colunas

Em [srcs/execution/drawmap.c](srcs/execution/drawmap.c), `draw_map()` faz isto:

- Verifica se o jogo esta valido.
- Para cada `x` da largura do ecran:
  - Prepara o raio (`prep_ray()`)
  - Se tudo ok, desenha a coluna (`draw_column()`)

Isto e a definicao de raycasting classico: um raio por coluna.

### `prep_ray()` - preparar e medir o raio

Este passo cria tudo o que e necessario para a coluna:

1. `init_ray()` cria a direcao do raio.
2. `cast_dda()` anda no mapa ate encontrar parede.
3. `calc_wall_height()` calcula a altura da parede.
4. Guarda a distancia no `zbuffer`.
5. Seleciona a textura correta (`select_texture()`).

Se algo falha (altura invalida ou textura nula), a coluna nao e desenhada.

## Parte 1: `init_ray()` - converter coluna do ecran em direcao 2D

Em [srcs/execution/raycasting.c](srcs/execution/raycasting.c), `init_ray()` faz:

1. Converte a coluna `x` para o intervalo de camera $[-1, 1]$:

$$
\text{camerax} = 2 \cdot x / \text{screenWidth} - 1
$$

2. Mistura a direcao do jogador com o plano da camera:

$$
\text{rayDir} = \text{dir} + \text{plane} \cdot \text{camerax}
$$

Isto cria um leque de raios: os do centro seguem a direcao do jogador, os das laterais abrem para a esquerda/direita.

### Traducao super simples

- Pensa no teu ecran como uma regua de -1 a 1.
- Cada ponto nessa regua da uma direcao ligeiramente diferente.
- Essa direcao vai ser o raio que procuras.

## Parte 2: `cast_dda()` - andar no mapa ate bater numa parede

O mapa e um grid de blocos. O DDA (Digital Differential Analyzer) avanca quadrado a quadrado na direcao do raio.

### 2.1 `init_dda_params()` - prepara distancias basicas

Em [srcs/execution/raycasting_utils.c](srcs/execution/raycasting_utils.c):

- `mapx` e `mapy` sao a celula atual do jogador (parte inteira de `px`, `py`).
- `deltadistx` e `deltadisty` dizem quanto o raio anda para atravessar uma linha vertical ou horizontal do grid.

Formula (intuitiva):

$$
\text{deltadistx} = |1 / \text{raydirx}| \quad\quad \text{deltadisty} = |1 / \text{raydiry}|
$$

Se `raydirx` ou `raydiry` forem 0, usa-se um numero enorme (1e30) para evitar divisao por zero.

### 2.2 `init_steps()` - escolher para que lado andar

Aqui define-se:

- `stepx` = +1 se o raio vai para a direita, -1 se vai para a esquerda.
- `stepy` = +1 se o raio vai para baixo, -1 se vai para cima.

E calcula-se `sidedistx` e `sidedisty`: a distancia ate a proxima linha vertical/horizontal do grid.

### 2.3 `run_dda_loop()` - o loop de passos no grid

Em [srcs/execution/raycasting.c](srcs/execution/raycasting.c):

- Compara `sidedistx` e `sidedisty`.
- Avanca na menor (isto significa bater primeiro numa linha vertical ou horizontal).
- Atualiza `mapx` ou `mapy`.
- Verifica se saiu do mapa ou se encontrou parede `'1'`.

No fim, `rt->side` indica o tipo de parede:

- `side == 0` -> bateu numa parede vertical (paredes E/W)
- `side == 1` -> bateu numa parede horizontal (paredes N/S)

### 2.4 `compute_perp_dist()` - distancia correta para o ecran

A distancia usada para desenhar nao e a distancia do raio direto, mas a distancia perpendicular (para evitar distorcao fish-eye).

```
if side == 0:
  perpwalldist = sidedistx - deltadistx
else:
  perpwalldist = sidedisty - deltadisty
```

Se ficar <= 0, usa-se um valor muito grande para evitar bugs.

## Parte 3: `calc_wall_height()` - converter distancia em altura no ecran

Em [srcs/execution/raycasting.c](srcs/execution/raycasting.c):

- A altura da parede no ecran e inversamente proporcional a distancia:

$$
\text{lineheight} = \text{screenHeight} / \text{perpwalldist}
$$

- `drawstart` e `drawend` limitam a coluna ao centro do ecran.

Isto faz paredes perto parecerem grandes e paredes longe pequenas.

## Parte 4: escolher textura (N/S/E/W)

Em [srcs/execution/drawmap.c](srcs/execution/drawmap.c), `select_texture()`:

- Se `side == 0` (vertical):
  - `raydirx < 0` -> textura Oeste (`WE`)
  - `raydirx >= 0` -> textura Este (`EA`)

- Se `side == 1` (horizontal):
  - `raydiry < 0` -> textura Norte (`NO`)
  - `raydiry >= 0` -> textura Sul (`SO`)

Isto garante que cada parede tem a textura correta.

## Parte 5: desenhar a coluna com textura

`draw_column()` e o final de tudo. Ele pega na coluna do ecran e pinta pixel a pixel.

### 5.1 `calc_tex_x()` - escolher a coluna dentro da textura

1. Calcula o ponto exato de impacto na parede (`wall_x`).
2. Fica so com a parte decimal (0..1).
3. Converte isso num `x` da textura.

Depois faz um espelho dependendo do lado, para a textura nao ficar invertida.

### 5.2 Calcular `step` e `tex_pos`

- `step`: quanto se deve andar na textura por cada pixel do ecran.

$$
\text{step} = \text{texHeight} / \text{lineheight}
$$

- `tex_pos`: posicao inicial na textura.

### 5.3 Loop vertical da coluna

Para cada `y` entre `drawstart` e `drawend`:

- Converte `tex_pos` num `y` da textura.
- Vai buscar a cor com `get_texel()`.
- Se `side == 1`, escurece um pouco (simula sombra).
- Desenha o pixel com `put_pixel()`.

Resultado: uma coluna texturada que representa uma parede 3D.

## O papel do `zbuffer`

Em `prep_ray()`:

- Guarda-se `perpwalldist` em `game->zbuffer[x]`.

Isto serve para outras coisas (por exemplo sprites) saberem se estao atras de uma parede.

## Resumo super simples (em linguagem mesmo basica)

- Imagina que o ecran e feito de 1280 colunas.
- Cada coluna dispara um laser.
- O laser anda pelo mapa quadrado ate bater numa parede.
- Mede a distancia e pinta uma coluna com textura.
- Repete 1280 vezes e tens o 3D.

## Exemplo mental rapido

Supondo que estas no meio do mapa e a parede esta a 3 blocos:

- O raio anda 3 quadrados.
- `perpwalldist = 3`.
- `lineheight = screenHeight / 3`.
- A coluna aparece com 1/3 da altura do ecran.

Se a parede estiver a 1 bloco:

- `perpwalldist = 1`.
- `lineheight = screenHeight / 1` (quase altura total).

## Pseudocodigo (forma curta)

```c
for x in [0..screenWidth-1]:
  init_ray(x)
  cast_dda()
  calc_wall_height()
  select_texture()
  draw_column()
```

## Pequenas notas que ajudam a entender

- O mapa e um grid de chars. `'1'` e parede. `0` e vazio.
- O jogador nao esta exatamente no centro do quadrado; usa-se `+0.5` para o centro.
- O DDA e so um jeito eficiente de andar quadrado a quadrado.
- O `side` serve para saber se bateu numa parede vertical ou horizontal.
- Escurecer a parede quando `side == 1` da um efeito de luz simples.

## Se quiseres estudar a fundo (ordem recomendada)

1. [includes/cub3d.h](includes/cub3d.h) para entender as structs.
2. [srcs/execution/drawmap.c](srcs/execution/drawmap.c) para o loop principal.
3. [srcs/execution/raycasting.c](srcs/execution/raycasting.c) para o DDA.
4. [srcs/execution/raycasting_utils.c](srcs/execution/raycasting_utils.c) para os detalhes matematicos.
5. [srcs/execution/drawer_utils.c](srcs/execution/drawer_utils.c) para textura e pixel.

## Checklist para auto-explicacao (treino)

Tenta responder isto sem olhar no codigo:

- Como se calcula a direcao de um raio a partir de `x`?
- Porque usamos `perpwalldist` e nao a distancia real do raio?
- Como o DDA decide se avanca no X ou no Y?
- Como escolhes a textura correta da parede?
- Como transformas a altura da parede em pixeis na tela?

Se conseguires responder, ja tens o essencial dominado.
