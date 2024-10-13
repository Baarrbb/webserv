<!DOCTYPE html>
<html lang="fr">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Test PHP - Ça fonctionne !</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            background-color: #f4f4f4;
            color: #333;
            margin: 0;
            padding: 0;
        }
        .container {
            max-width: 800px;
            margin: 50px auto;
            background-color: white;
            padding: 20px;
            box-shadow: 0 0 15px rgba(0, 0, 0, 0.1);
            border-radius: 8px;
        }
        h1 {
            color: #007BFF;
            text-align: center;
        }
        p {
            font-size: 1.2em;
        }
        .info-box {
            background-color: #007BFF;
            color: white;
            padding: 10px;
            border-radius: 5px;
            margin-bottom: 20px;
        }
        .phpinfo {
            margin-top: 30px;
            padding: 10px;
            background-color: #f9f9f9;
            border: 1px solid #ddd;
            border-radius: 5px;
            overflow-x: auto;
        }
        footer {
            text-align: center;
            margin-top: 50px;
            font-size: 0.9em;
            color: #666;
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>Test PHP : Ça fonctionne !</h1>
        
        <div class="info-box">
            <?php
                // Affichage de la date et heure actuelles
                echo "<p>Date et heure actuelles : " . date("Y-m-d H:i:s") . "</p>";
            ?>
        </div>
        
        <p>Bienvenue sur votre serveur PHP ! Si vous voyez cette page, cela signifie que PHP est correctement configuré et que le serveur fonctionne bien.</p>
        
        <div class="phpinfo">
            <h2>Informations PHP</h2>
            <?php
                // Afficher un résumé de phpinfo (version de PHP et autres informations)
                phpinfo(INFO_GENERAL); // Affiche les informations générales sur PHP
            ?>
        </div>
    </div>

    <footer>
        <p>&copy; 2024 - Test PHP par <strong>Votre Nom</strong></p>
    </footer>
</body>
</html>
