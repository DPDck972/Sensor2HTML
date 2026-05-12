# Sensor2HTML

Sistema distribuído com ESP8266 para captura de eventos de sensores e visualização em tempo real via interface web.

O projeto utiliza dois dispositivos ESP8266:

- Um ESP8266 atuando como **servidor embarcado** com dashboard HTML.
- Um ESP8266 atuando como **cliente sensor**, responsável por detectar eventos físicos e enviar dados via HTTP.

---

# Visão Geral

O objetivo do projeto é transformar eventos físicos detectados por sensores em dados visualizados diretamente no navegador.

Fluxo do sistema:

```text
[SENSOR GPIO]
      ↓
ESP8266 Cliente
      ↓ HTTP POST
ESP8266 Servidor
      ↓
Dashboard HTML em tempo real
```

O sistema cria uma arquitetura local totalmente embarcada:

- O servidor cria um Access Point Wi‑Fi.
- O cliente conecta automaticamente nesse AP.
- O cliente envia eventos JSON via HTTP POST.
- O servidor disponibiliza um dashboard web com atualização automática.

---

# Estrutura do Projeto

```text
Sensor2HTML/
│
├── client/
│   ├── client.ino
│   ├── config.h
│   ├── sensor.cpp
│   ├── sensor.h
│   └── WiFiManager.h
│
├── server_embarcado/
│   ├── server_embarcado.ino
│   ├── Config.h
│   ├── HtmlPage.h
│   ├── WebHandlers.h
│   └── WiFiManager.h
│
└── .gitattributes
```

---

# Arquitetura

## 1. ESP8266 Cliente

Responsável por:

- Ler sensores digitais.
- Detectar eventos usando interrupções.
- Enviar dados JSON via HTTP.
- Conectar automaticamente ao servidor.

### Sensor utilizado

O código foi implementado para um:

- Sensor seguidor de linha.

Ligado na GPIO5 (D1 do NodeMCU).

---

## 2. ESP8266 Servidor

Responsável por:

- Criar um Access Point Wi‑Fi.
- Receber eventos HTTP.
- Armazenar último evento recebido.
- Exibir dashboard HTML.
- Servir API REST.

O servidor opera em:

```text
WIFI_AP_STA
```

Ou seja:

- Access Point para os sensores.
- Station Mode para acesso externo.

---

# Funcionalidades

## Cliente

- Detecção por interrupção.
- Baixa latência.
- Envio HTTP POST.
- Logs via Serial.
- Estrutura orientada a objetos.
- Reconexão Wi‑Fi simples.

## Servidor

- Dashboard HTML embarcado.
- API REST.
- Modo dual Wi‑Fi.
- Atualização automática da interface.
- Contador de eventos.
- Resposta JSON.
- Tratamento de rotas.
- Monitoramento Serial.

---

# APIs Disponíveis

## GET /

Retorna a página HTML principal.

### Exemplo

```http
GET /
```

---

## GET /data

Retorna os últimos dados recebidos.

### Resposta

```json
{
  "counter": 12,
  "time": 152,
  "data": {
    "sensor": "line_follower",
    "state": "DETECTED",
    "timestamp": 10512
  }
}
```

---

## POST /api/sensor

Recebe dados enviados pelos sensores.

### Exemplo

```http
POST /api/sensor
Content-Type: application/json
```

### Payload

```json
{
  "sensor": "line_follower",
  "state": "DETECTED",
  "timestamp": 10512
}
```

### Resposta

```json
{
  "status": "received",
  "count": 13
}
```

---

# Explicação Arquivo por Arquivo

# CLIENTE

## client/client.ino

Arquivo principal do cliente.

Responsabilidades:

- Inicialização Serial.
- Conexão Wi‑Fi.
- Inicialização do sensor.
- Loop principal.
- Detecção de eventos.
- Envio de POST.

Principais configurações:

```cpp
const char* SSID
const char* PASSWORD
const char* SERVER_IP
```

O loop principal:

```cpp
if (lineFollower.CheckEvent())
```

Verifica se houve mudança de estado no sensor.

---

## client/config.h

Centraliza configurações globais do cliente.

Contém:

- SSID.
- Senha.
- IP do servidor.
- Porta.
- Baud rate.
- Timeout.

Permite desacoplamento das configurações.

---

## client/sensor.h

Define a classe `Sensor`.

A classe encapsula:

- GPIO.
- Estado atual.
- Estado anterior.
- Timestamp.
- Interrupções.
- Envio HTTP.

Métodos principais:

```cpp
Initialize()
CheckEvent()
PostEvent()
ResetEvent()
PrintDebug()
```

---

## client/sensor.cpp

Implementação da classe `Sensor`.

### Principais responsabilidades

#### Interrupção de hardware

```cpp
attachInterrupt()
```

Usada para detectar mudanças instantaneamente.

#### Captura de estado

```cpp
digitalRead(pin)
```

#### Envio HTTP

Utiliza:

```cpp
HTTPClient
WiFiClient
```

O payload enviado:

```json
{
  "sensor":"line_follower",
  "state":"DETECTED",
  "timestamp":12345
}
```

#### Debug Serial

O método:

```cpp
PrintDebug()
```

Exibe:

- Estado atual.
- Estado anterior.
- Timestamp.
- GPIO.

---

## client/WiFiManager.h

Gerencia conexão Wi‑Fi do cliente.

Responsabilidades:

- Conectar ao AP do servidor.
- Mostrar IP.
- Mostrar MAC Address.
- Mostrar RSSI.
- Monitorar status.

Modo utilizado:

```cpp
WIFI_STA
```

---

# SERVIDOR

## server_embarcado/server_embarcado.ino

Arquivo principal do servidor.

Responsabilidades:

- Inicialização Serial.
- Inicialização do Wi‑Fi.
- Inicialização do servidor HTTP.
- Configuração do AP.
- Logs de boot.
- Loop HTTP.

O servidor usa:

```cpp
ESP8266WebServer
```

Loop principal:

```cpp
server.handleClient();
```

---

## server_embarcado/Config.h

Centraliza configurações do servidor.

Contém:

- SSID externo.
- Senha externa.
- SSID do AP.
- Senha do AP.
- Porta HTTP.
- Baud rate.
- Timeout.
- Intervalos.

---

## server_embarcado/HtmlPage.h

Contém toda a dashboard HTML embarcada.

A página possui:

- Interface responsiva.
- Atualização automática.
- Exibição do último evento.
- Contador de eventos.
- Exibição de timestamps.
- Consumo da API `/data`.

Tecnologias utilizadas:

- HTML.
- CSS.
- JavaScript.
- Fetch API.

A atualização ocorre usando:

```javascript
fetch('/data')
```

---

## server_embarcado/WebHandlers.h

Implementa todas as rotas HTTP.

### handleRoot()

Retorna dashboard HTML.

### handleGetData()

Retorna JSON com:

- Dados.
- Timestamp.
- Contador.

### handlePostData()

Recebe os dados do sensor.

Responsabilidades:

- Armazenar payload.
- Atualizar timestamp.
- Incrementar contador.
- Retornar JSON.

### handleNotFound()

Tratamento de erro 404.

### setupWebServer()

Registra todas as rotas:

```cpp
/
/data
/api/sensor
```

---

## server_embarcado/WiFiManager.h

Gerencia Wi‑Fi em modo dual.

Modo:

```cpp
WIFI_AP_STA
```

Responsabilidades:

### Access Point

Cria rede:

```text
Sensor2HTML_Server
```

### Station Mode

Conecta em rede externa.

### Monitoramento

Exibe:

- IP.
- Gateway.
- RSSI.
- Clientes conectados.
- MAC Address.

---

# Como Executar

# Requisitos

## Hardware

- 2x ESP8266.
- Sensor digital.
- Cabo USB.

## Software

- Arduino IDE.
- ESP8266 Board Package.

---

# Bibliotecas Necessárias

Instale:

```text
ESP8266WiFi
ESP8266HTTPClient
ESP8266WebServer
```

---

# Configuração

## 1. Servidor

Abra:

```text
server_embarcado/server_embarcado.ino
```

Configure:

```cpp
const char* EXTERNAL_SSID
const char* EXTERNAL_PASSWORD
```

Faça upload para o ESP8266.

---

## 2. Cliente

Abra:

```text
client/client.ino
```

Configure se necessário:

```cpp
const char* SSID
const char* PASSWORD
const char* SERVER_IP
```

Faça upload para o ESP8266.

---

# Utilização

## Passo 1

Ligue o servidor.

Ele criará:

```text
SSID: Sensor2HTML_Server
Senha: sensor2html123
```

---

## Passo 2

Ligue o cliente.

Ele conectará automaticamente.

---

## Passo 3

Abra no navegador:

```text
http://IP_DO_SERVIDOR
```

---

# Exemplo de Fluxo

1. Sensor detecta linha.
2. Interrupção é disparada.
3. Cliente gera JSON.
4. Cliente envia POST.
5. Servidor recebe evento.
6. Dashboard atualiza.

---

# Conceitos Utilizados

## Sistemas Embarcados

- ESP8266.
- GPIO.
- Interrupções.
- Serial.
- Wi‑Fi.

## Redes

- HTTP.
- REST.
- Access Point.
- Station Mode.
- JSON.

## Desenvolvimento Web

- HTML.
- CSS.
- JavaScript.
- Fetch API.

## Programação

- C++.
- OOP.
- Encapsulamento.
- Callbacks.
- Eventos.

---

# Possíveis Melhorias

- WebSocket em tempo real.
- Múltiplos sensores.
- Banco de dados.
- Histórico persistente.
- OTA Update.
- Autenticação.
- HTTPS.
- Dashboard com gráficos.
- Suporte ESP32.
- FreeRTOS.

---

# Segurança

Atualmente o projeto:

- Usa HTTP simples.
- Não possui autenticação.
- Utiliza senha fixa.

Para produção recomenda-se:

- HTTPS.
- Tokens.
- MQTT TLS.
- Rotação de credenciais.

---

# Objetivo Educacional

O projeto é excelente para aprendizado de:

- IoT.
- ESP8266.
- Comunicação embarcada.
- Dashboards embarcados.
- APIs REST.
- Sensores digitais.
- Sistemas distribuídos.

---

# Licença

Projeto open-source para fins educacionais e experimentais.
