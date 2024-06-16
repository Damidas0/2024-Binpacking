import json
import matplotlib.pyplot as plt

import json

def json_to_latex_table(data):
    # Charger les données JSON
    instances = data['instances']
    
    # Entête du tableau LaTeX
    latex_table = "\\begin{table}[h!]\n"
    latex_table += "\\centering\n"
    latex_table += "\\begin{tabular}{|c|c|c|}\n"
    latex_table += "\\hline\n"
    latex_table += "Instance & Fitness & Temps d'exécution (ms) \\\\ \n"
    latex_table += "\\hline\n"
    
    # Ajouter chaque ligne du tableau
    for instance in instances:
        instance_num = instance['instance']
        fitness = instance['fitness']
        execution_time = instance['execution_time']
        
        # Formater les nombres à virgule flottante pour assurer la précision et la lisibilité
        fitness_str = f"{fitness:.5f}"
        execution_time_str = f"{execution_time:.0f}"
        
        latex_table += f"{instance_num} & {fitness_str} & {execution_time_str} \\\\ \n"
    
    # Pied de tableau LaTeX
    latex_table += "\\hline\n"
    latex_table += "\\end{tabular}\n"
    latex_table += "\\caption{Résultats des instances}\n"
    latex_table += "\\label{tab:resultats}\n"
    latex_table += "\\end{table}\n"
    
    return latex_table







def plot_fitness_from_json(json_file):
    with open(json_file, 'r') as f:
        data = json.load(f)
    
    fitness_values = data['fitness_values']
    iterations = range(0, len(fitness_values) * 2, 2)  # Indices des itérations (0, 10, 20, ...)
    
    # Calculer l'évolution de la meilleure fitness rencontrée jusqu'à chaque itération
    best_so_far = float('inf')  # Initialiser avec une valeur infinie
    best_fitness_values = []
    for fitness in fitness_values:
        if fitness < best_so_far:
            best_so_far = fitness
        best_fitness_values.append(best_so_far)
    
    plt.figure(figsize=(10, 6))
    plt.plot(iterations, fitness_values, marker='o', linestyle='-', color='b', label='Fitness')
    plt.plot(iterations, best_fitness_values, marker='x', linestyle='--', color='r', label='Meilleure Fitness')
    plt.title('Évolution de la Fitness au fil des Itérations')
    plt.xlabel('Itérations')
    plt.ylabel('Fitness')
    plt.grid(True)
    plt.legend()
    plt.tight_layout()
    plt.show()





if __name__ == '__main__':
    json_files = "results/resultsTabou.json"
    fitness_files = "results/fitness_values.json"
    with open(json_files, 'r') as f:
        data = json.load(f)

    print(json_to_latex_table(data))
    plot_fitness_from_json(fitness_files)

