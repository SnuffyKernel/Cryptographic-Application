const { ipcRenderer } = require("electron");
let OnOffCript = 0;
let OnOffFile = 0;

const vigenerInput = document.getElementById("vigenerInput");
const playfairInput = document.getElementById("playfairInput");
const enigmaInput = document.getElementById("enigmaInput");
const md5Input = document.getElementById("md5Input");

minimizeBtn.addEventListener("click", () => {
  ipcRenderer.send("minimizeApp");
});

maxResBtn.addEventListener("click", () => {
  ipcRenderer.send("maxinizeRestoreApp");
});

closeBtn.addEventListener("click", () => {
  ipcRenderer.send("closeApp");
});

password.addEventListener("click", () => {
  ipcRenderer.send("enter", passwordInput.value);
});

ipcRenderer.on("hashedPassword", (event, hashedPassword, isRedirected) => {
  if (hashedPassword === "c4ca4238a0b923820dcc509a6f75849b") {
    if (!isRedirected) {
      ipcRenderer.send("enter", isRedirected);
      window.location.href = "../html/main.html";
    }
    if (vigenerInput) ipcRenderer.send("vigener", vigenerLetterInput.value, vigenerKeyInput.value, vigenerInput.value, OnOffCript, OnOffFile);
    if (playfairInput) ipcRenderer.send("playfair", playfairLetterInput.value, playfairKeyInput.value, playfairInput.value, playfairColumnsInput.value, playfairCharacterInput.value,OnOffCript, OnOffFile);
    if (enigmaInput) ipcRenderer.send("enigma", enigmaLetterInput.value, enigmaRot1Input.value, enigmaRot2Input.value, enigmaRot3Input.value,enigmaReflectorInput.value, enigmaInput.value, OnOffFile);
    if (md5Input) ipcRenderer.send("md5", md5Input.value, md5KeyInput.value, OnOffFile);
  } else {
    errorMessage.textContent = "Неверный пароль";
    errorMessage.classList.add("shake-animation");
    errorMessage.addEventListener("animationend", function () {
      errorMessage.classList.remove("shake-animation");
    });
  }
});

ipcRenderer.on("vigenerCript", (event, vigenerEnDe) => {
  if (vigenerEnDe.startsWith("ERROR: ")) vigenerOutput.style.color = "red";
  else vigenerOutput.style.color = "white";
  vigenerOutput.value = vigenerEnDe;
});

ipcRenderer.on("playfairCript", (event, playfairEnDe) => {
  if (playfairEnDe.startsWith("ERROR: ")) playfairOutput.style.color = "red";
  else playfairOutput.style.color = "white";
  playfairOutput.value = playfairEnDe;
});

ipcRenderer.on("enigmaCript", (event, enigmaEnDe)=>{
  if (enigmaEnDe.startsWith("ERROR: ")) enigmaOutput.style.color = "red";
  else enigmaOutput.style.color = "white";
  enigmaOutput.value = enigmaEnDe;
});

ipcRenderer.on("md5Hash", (event, md5Hash)=>{
  if (md5Hash.startsWith("ERROR: ")) md5Output.style.color = "red";
  else md5Output.style.color = "white";
  md5Output.value = md5Hash;
});

decryptBtnFile.addEventListener("click", () => {
  decryptBtnFile.classList.toggle("active");
  file.classList.toggle("active");
  if (decryptBtnFile.classList.contains("active")) {
    OnOffFile = 1;
  } else {
    OnOffFile = 0;
  }
});

decryptBtnText.addEventListener("click", () => {
  decryptBtnText.classList.toggle("active");
  text.classList.toggle("active");
  if (decryptBtnText.classList.contains("active")) {
    if (vigenerInput) {
      vigenerInput.placeholder = "Введите текст для дешифрования";
      vigenerOutput.placeholder = "Здесь будет ваше расшифрованное сообщение";
    }
    if (playfairInput) {
      playfairInput.placeholder = "Введите текст для дешифрования";
      playfairOutput.placeholder = "Здесь будет ваше расшифрованное сообщение";
    }
    password.textContent = "Расшифровать";
    OnOffCript = 1;
  }
  else {
    if (vigenerInput) {
      vigenerInput.placeholder = "Введите текст для шифрования";
      vigenerOutput.placeholder = "Здесь будет ваше зашифрованное сообщение";
    }
    if (playfairInput) {
      playfairInput.placeholder = "Введите текст для шифрования";
      playfairOutput.placeholder = "Здесь будет ваше зашифрованное сообщение";
    }
    password.textContent = "Зашифровать";
    OnOffCript = 0;
  }
});

function vigenerhtml() {
  window.location.href = "../html/vigener.html";
}

function playfairhtml() {
  window.location.href = "../html/playfair.html";
}

function enigmahtml() {
  window.location.href = "../html/enigma.html";
}

function md5(){
   window.location.href = "../html/md5.html";
}

function backhtml() {
  history.back();
}