import json

def json_to_latex_table(json_file):
    # Charger les données JSON à partir du fichier
    with open(json_file, 'r') as f:
        data = json.load(f)

    latex_table = r'''\begin{table}[ht]
    \centering
    \begin{tabularx}{\textwidth}{ccc}
        \toprule
        \textbf{Instance} & \textbf{Stratégie longer left over} \\
        \midrule'''

    for instance_data in data['instances']:
        instance = instance_data['instance']
        fitness = instance_data['fitness']
        latex_table += f'\n{instance} & {fitness:.5f} \\\\'
    
    latex_table += r'''
    \bottomrule
    \end{tabularx}
    \caption{Comparaison des instances et fitness avec différentes stratégies}
    \label{tab:combined-table}
\end{table}'''

    return latex_table

if __name__ == '__main__':
    json_file = 'results/resultsNaive_StrategyshorterLeftover.json'  
    table_latex = json_to_latex_table(json_file)
    print(table_latex)  
