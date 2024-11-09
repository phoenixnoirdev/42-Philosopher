# Philosopher-42

## Ce projet enseigne la notion de Thread et Mutex.
### Le projet consiste à faire vivre X Philosophers à la fois comme un fil, chacun doit manger, penser et dormir.

Chaque action d'un philosophe doit être sortie comme ceci : timestamp_in_ms X has taken a fork

⚠️ 1 philo ne peut manger qu'avec 2 fourchettes en main, et les fourchettes ne peuvent pas être partagées !

💬 Exemple : Si vous lancez 1 philosophe, il n'y aura qu'une seule fourchette, le philosophe ne pourra pas manger et il mourra après le temps indiqué en argument 1

📌 Lisez en.subject pour le sujet de ce 42 projet.


## Methode pour les test

Vous devez d'abord faire.
pour lancez ./philo avec 5 ou 6 arguments :

◦ [number_of_philosophers] : est le nombre de philosophes et aussi le nombre de fourchettes.

◦ [time_to_die] : est en millisecondes, si un philosophe ne commence pas à manger 'time_to_die' quelques millisecondes après le début de son dernier repas ou le début de la simulation, il meurt.

◦ [time_to_eat] : est en millisecondes et est le temps qu'il faut à un philosophe pour manger. Pendant ce temps, ils devront conserver les deux fourchettes.

◦ [time_to_sleep] : est en millisecondes et est le temps que le philosophe passera à dormir.

◦ [number_of_times_each_philosopher_must_eat] : l'argument est facultatif, si tous les philosophes mangent au moins 'number_of_times_each_philosopher_must_eat' la simulation s'arrêtera. Sauf précision, la simulation ne s'arrêtera qu'à la mort d'un philosophe.


## Comment lancer ?
./philo [arg1] [arg2] [arg3] [arg4] [arg5 (optionnel)]
