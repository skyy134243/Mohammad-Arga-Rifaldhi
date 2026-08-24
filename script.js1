const songs = [
  ["About You", "The 1975", 326, "About You.mp3"],
  ["Sesi Potret", "enau feat Ari Lasmana", 243, "Sesi Potret.mp3"],
  ["Jatuh Suka", "Tulus", 235, "Jatuh Suka.mp3"],
];

const $ = (id) => document.querySelector(id);

const title = $("#title");
const artist = $("#artist");
const link = $("#link");
const bar = $("#progress");
const now = $("#now");
const left = $("#left");
const status = $("#status");
const vinyl = $("#vinyl");
const list = $("#list");
const playBtn = $("#play");

const audio = new Audio();
let currentSongIndex = 0;
let isPlaying = false;

const formatTime = (seconds) => {
  if (isNaN(seconds)) return "0:00";
  const minutes = Math.floor(seconds / 60);
  const secs = String(Math.floor(seconds % 60)).padStart(2, "0");
  return `${minutes}:${secs}`;
};

function createSongItem(songData, index) {
  const item = document.createElement("a");
  item.className = "song-item" + (index === currentSongIndex ? " active" : "");
  item.href = "#";
  item.dataset.song = String(index);
  item.setAttribute("role", "listitem");

  const order = document.createElement("span");
  order.textContent = `0${index + 1}`;

  const name = document.createElement("span");
  name.textContent = songData[0]; // textContent -> aman dari HTML injection

  const play = document.createElement("span");
  play.textContent = "▶️";

  item.append(order, name, play);
  item.addEventListener("click", (e) => e.preventDefault());
  return item;
}

function updateUI() {
  const [name, singer] = songs[currentSongIndex];

  title.textContent = name;
  artist.textContent = singer;

  link.removeAttribute("href");
  link.style.cursor = "default";

  list.replaceChildren(...songs.map(createSongItem));

  status.textContent = isPlaying ? "Memutar" : "Jeda";
  playBtn.innerHTML = isPlaying ? "Ⅱ <span>Jeda</span>" : "▶ <span>Putar</span>";
  vinyl.classList.toggle("is-spinning", isPlaying);
}

function playAudio() {
  audio.play()
    .then(() => {
      isPlaying = true;
      updateUI();
    })
    .catch((err) => {
      console.error("Gagal memutar audio:", err);
      isPlaying = false;
      updateUI();
    });
}

// Fungsi untuk mengganti lagu
function changeSong(index) {
  currentSongIndex = index;
  const audioFile = songs[currentSongIndex][3];

  audio.src = audioFile;
  playAudio();
}

function togglePlay() {
  if (!audio.src) {
    audio.src = songs[currentSongIndex][3];
  }

  if (isPlaying) {
    audio.pause(); // Jeda lagu
    isPlaying = false;
    updateUI();
  } else {
    playAudio(); // Putar lagu (async, update state setelah berhasil)
  }
}

audio.addEventListener("loadedmetadata", () => {
  // Gunakan durasi asli dari file audio, bukan angka hardcoded di array
  bar.max = audio.duration;
});

audio.addEventListener("timeupdate", () => {
  const currentTime = audio.currentTime;
  const duration = audio.duration || songs[currentSongIndex][2];
  const percent = duration ? (currentTime / duration) * 100 : 0;

  bar.value = currentTime;
  bar.style.setProperty("--progress", `${percent}%`);

  now.textContent = formatTime(currentTime);
  left.textContent = `-${formatTime(duration - currentTime)}`;
});

audio.addEventListener("error", () => {
  console.error("Terjadi kesalahan saat memuat file audio:", audio.src);
  isPlaying = false;
  updateUI();
});

audio.addEventListener("ended", () => {
  changeSong((currentSongIndex + 1) % songs.length);
});

playBtn.onclick = togglePlay;
$("#next").onclick = () => changeSong((currentSongIndex + 1) % songs.length);
$("#prev").onclick = () => changeSong((currentSongIndex + songs.length - 1) % songs.length);

bar.oninput = () => {
  audio.currentTime = Number(bar.value);
  now.textContent = formatTime(audio.currentTime);
};

list.onclick = (event) => {
  const item = event.target.closest("[data-song]");
  if (item) {
    changeSong(Number(item.dataset.song));
  }
};

updateUI();
