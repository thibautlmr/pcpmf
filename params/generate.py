import csv
from datetime import datetime, timedelta
import random

# Définir les informations de base
actif_unique = "id_0"
prix_initial = 100.0
date_debut = datetime(2022, 3, 3, 0, 0, 0)
date_fin = datetime(2022, 9, 3, 0, 0, 0)
previous_price = prix_initial
# Générer les données
donnees = []
current_date = date_debut
while current_date <= date_fin:
    # Calculer le prix fluctuant autour de 100 avec une valeur aléatoire
    prix = prix_initial + random.uniform(-12, 12)  # Exemple de fluctuation aléatoire entre -5 et 5
    previous_price = prix
    # Ajouter les données à la liste
    donnees.append([actif_unique, current_date.strftime("%m/%d/%Y %H:%M:%S"), prix])

    # Passer à la prochaine date
    current_date += timedelta(days=1)

# Écrire les données dans un fichier CSV
with open("C:/Users/Erwan Izenic/Documents/COURS_3A/pcpmf/pcpmfProject/params/donnees_prix.csv", "w", newline="") as csvfile:
    csvwriter = csv.writer(csvfile)
    # Écrire l'en-tête
    csvwriter.writerow(["Id", "DateOfPrice", "Value"])
    # Écrire les données
    csvwriter.writerows(donnees)

print("Fichier généré avec succès : donnees_prix.csv")