const { exec } = require('child_process');

exec('notepad', (err) => {
    if (err) {
        console.error('Faild to open Notepad: ', err);
    } else {
        console.log('Notepad opened successfully!');
    }
});