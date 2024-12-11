# Deelopdracht 2 - Netwerk en Security Vervolg
- Raekwon Killop
## Inhoudsopgave

- [Installatie](#installatie)
    - [Benodigdheden](#benodigdheden)
    - [Building](#building)
    - [Uitvoering](#uitvoering)

## Installatie

### Benodigdheden
Zorg ervoor dat je de volgende benodigdheden hebt:

- [Docker](https://www.docker.com/products/docker-desktop/) 
- [Arduino IDE](https://www.arduino.cc/en/software)

### Het volgende heb je nodig om de bot te bouwen

- [ESP32](https://www.otronic.nl/nl/nodemcu-esp32-s-4mb-wroom-38-pins.html)
- [DHT22](https://www.distrelec.nl/nl/dht22-temperatuur-en-vochtigheidssensor-5v-adafruit-385/p/30129240)
- Jumpwires
- Micro USB kabel


### Building

#### Bot
1. Eerst is het de bedoeling om een [schakeling](https://github.com/Raekwon1603/Netwerken-Security-Vervolg/blob/main/SKETCH_bb.png) te maken. De ESP en DHT22 zijn verbonden met elkaar met de volgende pinnen: pin 1 van de DHT22 sluiten we aan op de 3.3V van de ESP. Pin 2 van de DHT22 sluiten we aan op de GPIO4  van de ESP. Pin 4 van de DHT22 sluiten we aan op de Ground van de ESP32. 

    (als er enige verwarring ontstaat zijn [hier](https://www.google.com/url?sa=i&url=https%3A%2F%2Flastminuteengineers.com%2Fesp32-pinout-reference%2F&psig=AOvVaw2nD_cULAiukdivdMcDJ_ws&ust=1680090021308000&source=images&cd=vfe&ved=0CBAQjRxqFwoTCICx6ZrF_v0CFQAAAAAdAAAAABAk) de pinnen van de ESP32)

2. Vervolgens is het de bedoeling dat we de bot_connection.ino file uploaden op de ESP32. In het secret.h bestand moet je ervoor zorgen dat de juiste ssid en pass zijn ingesteld. Op de Hogeschool Rotterdam gebruiken we voor de verbinding met de netwerkenbasis website de Tesla IoT wifi.

    (tijdens het uploaden moeten de vereiste libraries wel geinstalleerd zijn)
#### Webserver
1. Navigeer naar de map waar het bestand docker-compose.yml zich bevindt en voer de volgende command uit in je terminal (let op dat de map waarin je navigeert file sharing moet toestaan in de Docker settings):

```bash
$ docker compose up -d
```
2. Open een nieuw tabblad in je webbrowser op https://localhost. 

### Uitvoering 
1. Nu je op de webpagina bent kunnen we berichten versturen. De berichten die wij versturen op ons localhost pagina zijn ook te zien op het netwerkenbasis.com pagina. Ook is op onze localhost pagina  de output te zien van de netwerkenbasis.com pagina. Het is mogelijk om op de site in te loggen met de volgende gebruikernaam en wachtwoord.

    ```bash
    $ student:welkom01
    ```

2. Er zijn verschillende commando's die je nu kan uitvoeren:

    Voor het aanzetten van het LED lampjen op de ESP voer deze commando uit:

    ```bash
    $ BOT-1034155: led:aan
    ```

    Voor het opmeten van de temperatuur voer deze commando uit:
     ```bash
    $ BOT-1034155: temperatuur
    ```
    
    Voor het opmeten van de vochtigheid voer deze commando uit: 
    ```bash
    $ BOT-1034155: vochtigheid
    ```

    Voor het uitzetten van het LED lampje op de ESP voer deze commando uit:
    ```bash
    $ BOT-1034155: led:uit
    ```
#### Opmerking
**Let erop dat de commando's exact als hierboven worden uitgevoerd. De commando's zijn spatie en hoofdletter gevoelig.**
