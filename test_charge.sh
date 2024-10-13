#!/bin/bash

# # Nombre de requêtes à envoyer
# NUM_REQUESTS=1000

# # URL du serveur
# URL="http://127.0.0.1:8080/"

# # Fonction pour envoyer une requête et mesurer le temps de réponse
# send_request() {
#     (time curl -s -w "HTTP Code: %{http_code}, Time: %{time_total}\n" -o /dev/null $URL) 2>&1 | grep real
# }

# # Envoyer les requêtes en parallèle
# for i in $(seq 1 $NUM_REQUESTS); do
#     send_request &
# done

# # Attendre que toutes les requêtes soient terminées
# wait

# echo "All requests completed."



# Nombre de requêtes à envoyer
NUM_REQUESTS=1000

# URL du serveur
URL="http://127.0.0.1:8080/"

# Fonction pour envoyer une requête et mesurer le temps de réponse
send_request() {
    local request_num=$1
    (time curl -s -w "HTTP Code: %{http_code}, Time: %{time_total}\n" -o "requests/response_${request_num}.log" $URL) 2>&1 | grep real
}

# Envoyer les requêtes en parallèle
for i in $(seq 1 $NUM_REQUESTS); do
    send_request $i &
done

# Attendre que toutes les requêtes soient terminées
wait

echo "All requests completed."