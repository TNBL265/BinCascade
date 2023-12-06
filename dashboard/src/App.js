import React, { useState, useEffect } from 'react';
import binImage from './images/BinCascade.jpeg';

const App = () => {
  const [distance1, setDistance1] = useState('N/A');
  const [distance2, setDistance2] = useState('N/A');

  useEffect(() => {
    const ws = new WebSocket('ws://localhost:3001');

    ws.onopen = () => {
      console.log('Connected to WebSocket server!');
    };

    ws.onmessage = (event) => {
      const [d1, d2] = event.data.split(',');
      setDistance1(d1);
      setDistance2(d2);
    };

    ws.onerror = (error) => {
      console.error('WebSocket error:', error);
    };

    return () => {
      if (ws) {
        ws.close();
      }
    };
  }, []);

  const getBinStatus = (distance) => {
    return distance < 10 ? "FULL" : "Space Available";
  }

  return (
    <div style={{ display: 'flex', flexDirection: 'column', alignItems: 'center', marginTop: '50px' }}>
      <h1 style={{ fontSize: '3em', marginBottom: '30px' }}>BinCascade Dashboard</h1>
      <img src={binImage} alt="Smart Bin Image" style={{ width: '600px', marginBottom: '30px' }} />
      <table style={{ textAlign: 'center', border: '1px solid black', borderCollapse: 'collapse', width: '600px' }}>
        <thead>
          <tr>
            <th style={{ border: '1px solid black', padding: '10px' }}>Type</th>
            <th style={{ border: '1px solid black', padding: '10px' }}>Organic</th>
            <th style={{ border: '1px solid black', padding: '10px' }}>Inorganic</th>
          </tr>
        </thead>
        <tbody>
          <tr>
            <td style={{ border: '1px solid black', padding: '10px' }}>Distance</td>
            <td style={{ border: '1px solid black', padding: '10px' }}>{distance1} cm</td>
            <td style={{ border: '1px solid black', padding: '10px' }}>{distance2} cm</td>
          </tr>
          <tr>
            <td style={{ border: '1px solid black', padding: '10px' }}>Status</td>
            <td style={{ border: '1px solid black', padding: '10px' }}>{getBinStatus(distance1)}</td>
            <td style={{ border: '1px solid black', padding: '10px' }}>{getBinStatus(distance2)}</td>
          </tr>
        </tbody>
      </table>
    </div>
  );
};

export default App;
