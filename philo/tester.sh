#!/usr/bin/env bash

# Script utilisant un système de menus pour générer des paramètres du problème des philosophes.
# L'utilisateur choisit :
#  - Performance (Light, Normal, Hard, Extreme)
#  - Durée (courte, moyenne, longue)
#  - Meal limit (Non, 5-10, 10-20, 20-50)
#  - Fin (Un philosophe meurt ou pas)
#
# Le script génère ensuite:
#   philo_nbr, die_ms, eat_ms, sleep_ms, meal_limit
# en fonction des catégories choisies et des conditions de mort ou de survie.

random_range() {
    local min=$1
    local max=$2
    echo $((RANDOM % (max - min + 1) + min))
}

echo "=== Configuration du scénario ==="

# Menu Performance
echo "Sélectionnez le niveau de performance :"
options_perf=("Light (1-10)" "Normal (10-25)" "Hard (25-100)" "Extreme (100-200)")
select opt in "${options_perf[@]}"; do
    case $REPLY in
        1) philo_min=1; philo_max=10; break;;
        2) philo_min=10; philo_max=25; break;;
        3) philo_min=25; philo_max=100; break;;
        4) philo_min=100; philo_max=200; break;;
        *) echo "Option invalide";;
    esac
done

# Menu Durée
echo "Sélectionnez la durée :"
options_duree=("Courte" "Moyenne" "Longue")
select opt in "${options_duree[@]}"; do
    case $REPLY in
        1) # Courte
           die_min=100; die_max=300
           eat_min=50; eat_max=100
           sleep_min=50; sleep_max=100
           break;;
        2) # Moyenne
           die_min=300; die_max=800
           eat_min=100; eat_max=200
           sleep_min=100; sleep_max=200
           break;;
        3) # Longue
           die_min=800; die_max=2000
           eat_min=200; eat_max=400
           sleep_min=200; sleep_max=400
           break;;
        *) echo "Option invalide";;
    esac
done

# Menu Meal limit
echo "Sélectionnez la limite de repas (Meal limit) :"
options_meal=("Non" "5-10" "10-20" "20-50")
select opt in "${options_meal[@]}"; do
    case $REPLY in
        1) meal_limit="none"; break;;
        2) meal_min=5; meal_max=10; break;;
        3) meal_min=10; meal_max=20; break;;
        4) meal_min=20; meal_max=50; break;;
        *) echo "Option invalide";;
    esac
    break
done

# Menu Fin
echo "Est-ce qu'un philosophe doit mourir ?"
options_fin=("Oui (un philosophe meurt)" "Non (aucun ne meurt)")
select opt in "${options_fin[@]}"; do
    case $REPLY in
        1) doit_mourir=true; break;;
        2) doit_mourir=false; break;;
        *) echo "Option invalide";;
    esac
done

# Génération aléatoire des valeurs
philo_nbr=$(random_range $philo_min $philo_max)
die_ms=$(random_range $die_min $die_max)
eat_ms=$(random_range $eat_min $eat_max)
sleep_ms=$(random_range $sleep_min $sleep_max)

# Génération du meal_limit (si pas "none")
if [ "$meal_limit" != "none" ]; then
    meal_limit=$(random_range $meal_min $meal_max)
else
    meal_limit="" # vide si "none"
fi

# Ajustement selon la condition "meurt" ou "ne meurt pas"
threshold=$(( eat_ms + (sleep_ms * philo_nbr / 2) ))

if $doit_mourir; then
    if [ $die_ms -gt $threshold ]; then
        die_ms=$threshold
    fi
else
    if [ $die_ms -le $threshold ]; then
        die_ms=$((threshold + 50))
    fi
fi

# Affichage des paramètres générés
echo "=== Paramètres générés ==="
echo "Nombre de philosophes : $philo_nbr"
echo "die_ms : $die_ms"
echo "eat_ms : $eat_ms"
echo "sleep_ms : $sleep_ms"
if [ -n "$meal_limit" ]; then
    echo "meal_limit : $meal_limit"
else
    echo "meal_limit : none"
fi

if $doit_mourir; then
    echo "Dans ce scénario, un philosophe devrait finir par mourir."
else
    echo "Dans ce scénario, aucun philosophe ne devrait mourir."
fi

# Construction de la ligne de commande
if [ -n "$meal_limit" ]; then
    echo "./philo $philo_nbr $die_ms $eat_ms $sleep_ms $meal_limit"
else
    echo "./philo $philo_nbr $die_ms $eat_ms $sleep_ms"
fi