import json
import matplotlib.pyplot as plt
import matplotlib.patches as patches
from matplotlib.ticker import MaxNLocator
import json

def plot_binpacking(data):
    bins = data['bins']
    
    num_bins = len(bins)
    num_rows = (num_bins + 4) // 6  # Calcul du nombre de lignes pour la disposition des bins
    fig, axs = plt.subplots(num_rows, 6, figsize=(4 * 6, 4 * num_rows))
    axs = axs.flatten()
    
    for i, bin in enumerate(bins):
        ax = axs[i]
        bin_width = bin['dimensions']['width']
        bin_height = bin['dimensions']['height']
        
        ax.set_xlim(0, bin_width)
        ax.set_ylim(0, bin_height)
        ax.set_title(f'Bin {i + 1}', fontsize=12)
        ax.set_aspect('equal')
        ax.invert_yaxis()  # Inverse l'axe y pour que l'origine soit en haut à gauche

        ax.set_xticks([])
        ax.set_yticks([])
        
        # Draw the bin border
        ax.add_patch(patches.Rectangle((0, 0), bin_width, bin_height, edgecolor='black', facecolor='none'))
        
        # Liste des couleurs pour les rectangles
        colors = plt.cm.tab20.colors  # Utilisation de la palette de couleurs 'tab20'
        
        for j, rect in enumerate(bin['rectangles']):
            x, y = rect['x'], rect['y']
            width, height = rect['width'], rect['height']
            rect_id = rect['id']
            color = colors[j+i% len(colors)]  # Utilisation d'une couleur différente pour chaque rectangle
            
            ax.add_patch(patches.Rectangle((x, y), width, height, edgecolor='black', facecolor=color, alpha=0.5))
            ax.text(x + width / 2, y + height / 2, f'{rect_id}', ha='center', va='center', color='black', fontsize=8, fontweight='bold')
    
    # Masquer les axes des subplots non utilisés
    for j in range(num_bins, len(axs)):
        axs[j].axis('off')
    
    plt.tight_layout()
    plt.show()


def read_json_file(filename):
    with open(filename, 'r') as f:
        data = json.load(f)
    return data

#_______________________________________________________________________________________

filename = 'output.json'
data = read_json_file(filename)

plot_binpacking(data)


