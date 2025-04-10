const fs = require('fs');

const source = 'D:/OSLab-7Sem/file_copy/Dir1/my.txt';
const destination = 'D:/OSLab-7Sem/file_copy/Dir2/my.txt';

try {
    fs.copyFileSync(source, destination);
    console.log('File copied successfully!');
} catch (err) {
    if (err.code == "ENOENT")
        console.log("File not found.")
    else
        console.error('Error copying file:', err);
}
