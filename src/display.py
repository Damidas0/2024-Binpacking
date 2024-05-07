import os
import json
import matplotlib.pyplot as plt
from matplotlib.patches import Rectangle

def display_solution(json_file):
    # Obtention du chemin absolu du fichier JSON
    script_dir = os.path.dirname(os.path.abspath(__file__))
    json_path = os.path.join(script_dir, json_file)
    
    # Chargement des données depuis le fichier JSON
    with open(json_path, 'r') as f:
        data = json.load(f)
        
        # Création de la figure
        fig, ax = plt.subplots()
        
        # Initialisation de la position actuelle
        current_x = 0
        current_y = 0
        
        # Parcours des bins
        for bin_data in data["bins"]:
            bin_width = bin_data["dimensions"]["width"]
            bin_height = bin_data["dimensions"]["height"]
            
            # Ajout du conteneur
            ax.add_patch(Rectangle((current_x, current_y), bin_width, bin_height, edgecolor='black', facecolor='none'))
            
            # Ajout des rectangles dans le bin
            for rect in bin_data["rectangles"]:
                if rect["rotation"] == 0:
                    ax.add_patch(Rectangle((current_x + rect["x"], current_y + rect["y"]), rect["width"], rect["height"], edgecolor='blue', facecolor='lightblue'))
                    # Ajout du numéro de rectangle
                    ax.text(current_x + rect["x"] + rect["width"] / 2, current_y + rect["y"] + rect["height"] / 2, str(rect["id"]), color='black', fontsize=8, ha='center', va='center')
                else:
                    ax.add_patch(Rectangle((current_x + rect["x"], current_y + rect["y"]), rect["height"], rect["width"], angle=90, edgecolor='blue', facecolor='lightblue'))
                    # Ajout du numéro de rectangle
                    ax.text(current_x + rect["x"] + rect["height"] / 2, current_y + rect["y"] + rect["width"] / 2, str(rect["id"]), color='black', fontsize=8, ha='center', va='center')
            
            # Mise à jour de la position pour le prochain bin
            current_x += bin_width 
        
        ax.set_aspect('equal', 'box')
        ax.autoscale()
        plt.show()

# Utilisation de la fonction pour charger et afficher la solution depuis un fichier JSON
display_solution("testAffichage.json")
