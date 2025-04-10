const fs = require('fs');
const path = 'D:/OSLab-7Sem/file_append/data.txt';

//Message that want to append
const message = 'This is a new file';

//Append message with newline
fs.appendFile(path, message + '\n', (err) => {
    if (err) {
        console.error('Error writing to file: ', err);
    } else {
        console.log('Message appended sucsessfully!');
    }
});