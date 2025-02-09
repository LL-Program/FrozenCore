import pygame
import json
import os
import re
import math

TILE_SIZE = 16
WIDTH, HEIGHT = 800, 600
SPRITE_WIDTH = 1028
SPRITE_HEIGHT = 1028

pygame.init()
screen = pygame.display.set_mode((WIDTH, HEIGHT), pygame.RESIZABLE)
clock = pygame.time.Clock()

# Load the initial spritesheet
spritesheet_path = "src/resources/Env/tilemap2.png"
spritesheet = pygame.image.load(spritesheet_path)
sprite_cols, sprite_rows = int(spritesheet.get_height() / TILE_SIZE), int(spritesheet.get_width() / TILE_SIZE)

print(f"COLS: {sprite_cols}, ROWS: {sprite_rows}")

TILESET = [
    spritesheet.subsurface(pygame.Rect(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE))
    for y in range(sprite_rows) for x in range(sprite_cols)
]

# SPRITES
grid = {}
current_spritesheet = 0
current_tile = 0
blocking = 1

camera_x, camera_y = 0, 0
zoom = 2.0

dragging = False
last_mouse_x, last_mouse_y = 0, 0

# Scrolling variables
sprite_scroll_offset = 0

def load_spritesheet(filepath):
    global spritesheet, TILESET
    spritesheet = pygame.image.load(filepath)

    TILESET = [
        spritesheet.subsurface(pygame.Rect(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE))
        for y in range(sprite_rows) for x in range(sprite_cols)
    ]

running = True
while running:
    screen.fill((50, 50, 50))

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        elif event.type == pygame.KEYDOWN:
            if event.key == pygame.K_UP:
                current_tile = (current_tile - 1) % len(TILESET)
            elif event.key == pygame.K_DOWN:
                current_tile = (current_tile + 1) % len(TILESET)
            elif event.key == pygame.K_b:
                blocking = 1 - blocking
            elif event.key == pygame.K_s:
                with open("level.fcl", "w") as f:
                    for item in grid.items():
                        s, v = list(item)
                        f.write(f"{s[0]}X{s[1]}Y{v[0]}SH{v[1]}I{v[2]}B|")
            elif event.key == pygame.K_l:
                with open("level.fcl", "r") as f:
                    grid = {}
                    data = f.read().strip()
                    if data:
                        for entry in data.split("|"):
                            try:
                                match = re.match(r"(\d+)X(\d+)Y(\d+)SH(\d+)I(\d+)B", entry)
                                if match:
                                    x, y, sh, i, b = map(int, match.groups())
                                    grid[(x, y)] = (sh, i, b)
                                else:
                                    print(f"Fehler beim Parsen der Zeile: {entry}")
                            except ValueError:
                                print(f"Fehler beim Parsen der Zeile: {entry}")
            elif event.key == pygame.K_PLUS or event.key == pygame.K_EQUALS:
                zoom = min(4.0, zoom + 0.1)
            elif event.key == pygame.K_MINUS:
                zoom = max(0.5, zoom - 0.1)
            elif event.key == pygame.K_o:  # Load a new spritesheet
                file_path = input("Enter the path to the new spritesheet: ")
                if os.path.exists(file_path):
                    load_spritesheet(file_path)
                else:
                    print("Invalid file path.")
        elif event.type == pygame.MOUSEBUTTONDOWN:
            if event.button == 1:  # Left click to place sprite
                mx, my = pygame.mouse.get_pos()
                grid_x = math.floor((mx / zoom + camera_x) / TILE_SIZE)
                grid_y = math.floor((my / zoom + camera_y) / TILE_SIZE)

                grid[(grid_x, grid_y)] = (current_spritesheet, current_tile, blocking)

            elif event.button == 3:  # Right click to remove sprite
                mx, my = pygame.mouse.get_pos()
                grid_x = math.floor((mx / zoom + camera_x) / TILE_SIZE)
                grid_y = math.floor((my / zoom + camera_y) / TILE_SIZE)
                
                if (grid_x, grid_y) in grid:  # Ensure the tile exists before deleting
                    del grid[(grid_x, grid_y)]
            elif event.button == 2:  # Middle click to start dragging
                dragging = True
                last_mouse_x, last_mouse_y = pygame.mouse.get_pos()
        elif event.type == pygame.MOUSEBUTTONUP:
            if event.button == 2:  # Stop dragging when mouse is released
                dragging = False
        elif event.type == pygame.MOUSEMOTION:
            if dragging:  # Move the camera when dragging
                mx, my = pygame.mouse.get_pos()
                camera_x -= (mx - last_mouse_x) / zoom
                camera_y -= (my - last_mouse_y) / zoom
                last_mouse_x, last_mouse_y = mx, my
        elif event.type == pygame.MOUSEWHEEL:
            # Scroll through the sprite list
            if event.y > 0:  # Scroll up
                current_tile = max(0, current_tile - 1)
            elif event.y < 0:  # Scroll down
                current_tile = min(len(TILESET) - 1, current_tile + 1)

    # Get the current screen width and height
    screen_width, screen_height = screen.get_size()

    # Draw the full spritesheet in the top-right corner
    sprite_size = TILE_SIZE  # Adjust sprite size to fit into the corner
    sprite_start_x = screen_width - sprite_size * sprite_cols - 10  # Padding from the right
    sprite_start_y = 10  # Padding from the top

    # Draw the entire spritesheet in the top-right corner
    for i in range(sprite_rows):
        for j in range(sprite_cols):
            tile = TILESET[i * sprite_cols + j]
            x = sprite_start_x + j * sprite_size
            y = sprite_start_y + i * sprite_size
            scaled_tile = pygame.transform.scale(tile, (sprite_size, sprite_size))
            screen.blit(scaled_tile, (x, y))

    # Highlight the selected sprite in the spritesheet
    selected_x = sprite_start_x + (current_tile % sprite_cols) * sprite_size
    selected_y = sprite_start_y + (current_tile // sprite_cols) * sprite_size
    pygame.draw.rect(screen, (255, 255, 0), (selected_x, selected_y, sprite_size, sprite_size), 3)

    # Draw the grid with placed tiles
    for (x, y), (spr_idx, tile_idx, blk) in grid.items():
        tile = TILESET[tile_idx]
        scaled_tile = pygame.transform.scale(tile, (int(TILE_SIZE * zoom), int(TILE_SIZE * zoom)))
        screen.blit(scaled_tile, ((x * TILE_SIZE - camera_x) * zoom, (y * TILE_SIZE - camera_y) * zoom))
        if blk:
            pygame.draw.rect(screen, (255, 0, 0), ((x * TILE_SIZE - camera_x) * zoom, (y * TILE_SIZE - camera_y) * zoom, TILE_SIZE * zoom, TILE_SIZE * zoom), 2)

    pygame.draw.rect(screen, (0, 255, 0), ((0 * TILE_SIZE - camera_x) * zoom, (0 * TILE_SIZE - camera_y) * zoom, TILE_SIZE * zoom, TILE_SIZE * zoom), 2)
    # Display current tile properties and grid position
    font = pygame.font.Font(None, 24)
    mx, my = pygame.mouse.get_pos()
    grid_x = math.floor((mx / zoom + camera_x) / TILE_SIZE)
    grid_y = math.floor((my / zoom + camera_y) / TILE_SIZE)
    pos_text1 = font.render(f"Grid: {grid_x}, {grid_y}", True, (255, 255, 255))
    pos_text4 = font.render(f"Grid InGame: {grid_x * 48}, {grid_y * 48}", True, (255, 255, 255))
    pos_text2 = font.render(f"blocking: {blocking}", True, (255, 255, 255))
    pos_text3 = font.render(f"Tile Index: {current_tile}", True, (255, 255, 255))
    screen.blit(pos_text1, (10, 10))
    screen.blit(pos_text2, (10, 35))
    screen.blit(pos_text3, (10, 55))
    screen.blit(pos_text4, (10, 75))

    pygame.display.flip()
    clock.tick(60)

pygame.quit()
