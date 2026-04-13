#ifndef HTML_PAGE_H
#define HTML_PAGE_H

const char* HTML_PAGE = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Sensor2HTML - ESP8266 Server</title>
  <style>
    * {
      margin: 0;
      padding: 0;
      box-sizing: border-box;
    }
    body {
      font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
      background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
      min-height: 100vh;
      display: flex;
      justify-content: center;
      align-items: center;
      padding: 20px;
    }
    .container {
      background: white;
      border-radius: 10px;
      box-shadow: 0 10px 40px rgba(0,0,0,0.2);
      padding: 40px;
      max-width: 600px;
      width: 100%;
    }
    h1 {
      color: #333;
      margin-bottom: 10px;
      text-align: center;
    }
    .subtitle {
      color: #666;
      text-align: center;
      margin-bottom: 30px;
      font-size: 14px;
    }
    .info-box {
      background: #f5f5f5;
      border-left: 4px solid #667eea;
      padding: 20px;
      margin-bottom: 20px;
      border-radius: 5px;
    }
    .info-box h3 {
      color: #667eea;
      margin-bottom: 10px;
    }
    .data-display {
      background: #f9f9f9;
      padding: 15px;
      border-radius: 5px;
      margin: 10px 0;
      font-family: monospace;
      color: #333;
      word-break: break-all;
    }
    .status {
      display: inline-block;
      padding: 5px 10px;
      border-radius: 3px;
      font-size: 12px;
      font-weight: bold;
    }
    .status.online {
      background: #4CAF50;
      color: white;
    }
    .status.offline {
      background: #f44336;
      color: white;
    }
    .refresh-btn {
      background: #667eea;
      color: white;
      border: none;
      padding: 10px 20px;
      border-radius: 5px;
      cursor: pointer;
      font-size: 14px;
      width: 100%;
      margin-top: 20px;
      transition: background 0.3s;
    }
    .refresh-btn:hover {
      background: #764ba2;
    }
    .stat-box {
      background: white;
      border: 2px solid #e0e0e0;
      padding: 15px;
      border-radius: 5px;
      text-align: center;
    }
  </style>
</head>
<body>
  <div class="container">
    <h1>📊 Sensor2HTML</h1>
    <p class="subtitle">ESP8266 Data Receiver Server</p>
    
    <div class="info-box">
      <h3>📡 Server Status</h3>
      <p><span class="status online">● ONLINE</span></p>
      <p style="margin-top: 10px; color: #666; font-size: 14px;">Waiting for POST requests from remote sensor...</p>
    </div>

    <div class="info-box">
      <h3>� Statistics</h3>
      <div style="display: grid; grid-template-columns: 1fr 1fr; gap: 15px;">
        <div class="stat-box">
          <p style="font-size: 12px; color: #999;">Total Posts</p>
          <p style="font-size: 24px; font-weight: bold; color: #667eea;" id="counterContainer">0</p>
        </div>
        <div class="stat-box">
          <p style="font-size: 12px; color: #999;">Last Update</p>
          <p style="font-size: 14px; font-weight: bold; color: #333;" id="timeContainer">Waiting...</p>
        </div>
      </div>
    </div>

    <div class="info-box">
      <h3>📈 Last Received Data</h3>
      <div id="dataContainer" class="data-display">
        No data received yet
      </div>
    </div>

    <button class="refresh-btn" onclick="refreshData()">🔄 Refresh Data</button>
  </div>

  <script>
    function refreshData() {
      fetch('/data')
        .then(response => response.json())
        .then(data => {
          const container = document.getElementById('dataContainer');
          const timeContainer = document.getElementById('timeContainer');
          const counterContainer = document.getElementById('counterContainer');
          
          // Update counter
          if (data.counter !== undefined) {
            counterContainer.innerHTML = data.counter;
          }
          
          // Update last received data
          if (data.data) {
            // If data is an object (JSON), format it nicely
            if (typeof data.data === 'object') {
              let html = '<strong>Sensor Event Received:</strong><br>';
              html += 'State: <strong>' + (data.data.state || 'N/A') + '</strong><br>';
              html += 'Sensor: <strong>' + (data.data.sensor || 'N/A') + '</strong><br>';
              html += 'Timestamp: <strong>' + (data.data.timestamp || 'N/A') + '</strong>';
              container.innerHTML = html;
            } else {
              // If it's a string, just display it
              container.innerHTML = '<strong>Data:</strong> ' + JSON.stringify(data.data);
            }
            
            // Format time
            if (data.time) {
              timeContainer.innerHTML = new Date(data.time * 1000).toLocaleString();
            }
          } else {
            container.innerHTML = 'No data received yet';
            timeContainer.innerHTML = 'Waiting...';
          }
        })
        .catch(error => {
          console.error('Error:', error);
          document.getElementById('dataContainer').innerHTML = 'Error refreshing data: ' + error;
        });
    }
    
    // Auto-refresh every 2 seconds
    setInterval(refreshData, 2000);
    
    // Initial refresh
    refreshData();
  </script>
</body>
</html>
)rawliteral";

#endif // HTML_PAGE_H
