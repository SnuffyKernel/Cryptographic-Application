const { app, BrowserWindow, ipcMain } = require("electron");
const path = require("path");
const ipc = ipcMain;

function createWindow() {
  const mainWindow = new BrowserWindow({
    width: 1000,
    height: 650,
    frame: false,
    show: false,
    icon: path.join(__dirname, "../images/ico.ico"),
    webPreferences: {
      nodeIntegration: true,
      contextIsolation: false,
      devTools: true,
      preload: path.join(__dirname, "./src/js/preload.js"),
    },
  });

  mainWindow.loadFile("src/html/oauth.html");

  mainWindow.once("ready-to-show", () => {
    mainWindow.show();
  });

  mainWindow.webContents.on("did-finish-load", () => {
    if (loadingScreen) {
      loadingScreen.close();
    }
    mainWindow.show();
  });

  ipc.on("minimizeApp", () => {
    console.log("Clicked on Minimize Btn");
    mainWindow.minimize();
  });

  ipc.on("maxinizeRestoreApp", () => {
    if (mainWindow.isMaximized()) {
      console.log("Clicked on Restore");
      mainWindow.restore();
    } else {
      mainWindow.maximize();
    }
  });

  ipc.on("closeApp", () => {
    console.log("Clicked on Close Btn");
    mainWindow.close();
  });
}

let loadingScreen;
const createLoadingScreen = () => {
  loadingScreen = new BrowserWindow(
    Object.assign({
      width: 280,
      height: 380,
      frame: false,
      show: false,
      icon: path.join(__dirname, "../images/ico.ico"),
      webPreferences: {
        nodeIntegration: true,
        contextIsolation: false,
        devTools: true,
        preload: path.join(__dirname, "./src/js/preload.js"),
      },
    })
  );

  loadingScreen.once("ready-to-show", () => {
    loadingScreen.show();
  });

  loadingScreen.setResizable(false);
  loadingScreen.loadFile("src/html/loading.html");

  loadingScreen.on("closed", () => (loadingScreen = null));
  loadingScreen.webContents.on("did-finish-load", () => {
    loadingScreen.show();
  });
};

app.whenReady().then(() => {
  createLoadingScreen();
  setTimeout(() => {
    createWindow();
  }, 6000);

  app.on("activate", function () {
    if (BrowserWindow.getAllWindows().length === 0) createWindow();
  });
});

app.on("window-all-closed", function () {
  if (process.platform !== "darwin") app.quit();
});

const vigener = require("../cpp/vigener/build/Release/vigener");
const playfair = require("../cpp/playfair/build/Release/playfair");
const enigma = require("../cpp/enigma/build/Release/enigma");
const md5 = require("../cpp/md5/build/Release/md5");

let isRedirected = false;

ipc.on("enter", (event, password) => {
  event.reply("hashedPassword", md5.md5(password, "", 0), isRedirected);
  if (password === false) isRedirected = true;
});

ipc.on("vigener", (event, letter, keyInput, textInput, OnOffCript, OnOffFile) => {
  const vigenerEnDe = vigener.vigener(letter, keyInput, textInput, OnOffCript, OnOffFile);
  console.log("Encrypted/Decoded: ", vigenerEnDe);
  event.reply("vigenerCript", vigenerEnDe);
});

ipc.on("playfair", (event, letter, keyInput, textInput, ColumnsInput, CharacterInput, OnOffCript, OnOffFile) => {
  const playfairEnDe = playfair.playfair(letter, keyInput, textInput, CharacterInput, ColumnsInput, OnOffCript, OnOffFile);
  console.log("Encrypted/Decoded: ", playfairEnDe);
  event.reply("playfairCript", playfairEnDe);
});

ipc.on("enigma", (event, alf, rot1, rot2, rot3, reflector, text, OnOffFile)=>{
  const enigmaEnDe = enigma.enigma(alf, rot1, rot2, rot3, reflector, text, OnOffFile);
  console.log("Encrypted/Decoded: ", enigmaEnDe);
  event.reply("enigmaCript", enigmaEnDe);
});

ipc.on("md5", (event, text, symbolHash, OnOffFile)=>{
  const md5Hash = md5.md5(text, symbolHash, OnOffFile);
  console.log("Hash: ", md5Hash);
  event.reply("md5Hash", md5Hash);
});