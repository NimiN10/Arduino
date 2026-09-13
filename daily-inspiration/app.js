(function () {
  const FAVORITES_KEY = "dailyInspiration.favorites";
  const collection =
    typeof INSPIRATION_COLLECTION !== "undefined" && Array.isArray(INSPIRATION_COLLECTION)
      ? INSPIRATION_COLLECTION
      : [];

  const els = {
    date: document.getElementById("today-date"),
    type: document.getElementById("entry-type"),
    content: document.getElementById("entry-content"),
    source: document.getElementById("entry-source"),
    favoriteBtn: document.getElementById("favorite-btn"),
    anotherBtn: document.getElementById("another-btn"),
    toggleFavorites: document.getElementById("toggle-favorites"),
    favoritesLabel: document.getElementById("favorites-label"),
    favoritesList: document.getElementById("favorites-list"),
    favoritesCount: document.getElementById("favorites-count")
  };

  let currentEntry = null;

  function todayString() {
    const now = new Date();
    return now.toISOString().slice(0, 10); // YYYY-MM-DD
  }

  // Simple deterministic hash so the same date always picks the same entry.
  function hashString(str) {
    let hash = 0;
    for (let i = 0; i < str.length; i++) {
      hash = (hash << 5) - hash + str.charCodeAt(i);
      hash |= 0;
    }
    return Math.abs(hash);
  }

  function getDailyEntry() {
    if (collection.length === 0) return null;
    const index = hashString(todayString()) % collection.length;
    return collection[index];
  }

  function getRandomEntry(excludeId) {
    if (collection.length === 0) return null;
    if (collection.length === 1) return collection[0];
    let pick;
    do {
      pick = collection[Math.floor(Math.random() * collection.length)];
    } while (pick.id === excludeId);
    return pick;
  }

  function loadFavorites() {
    try {
      const raw = localStorage.getItem(FAVORITES_KEY);
      return raw ? JSON.parse(raw) : [];
    } catch (e) {
      return [];
    }
  }

  function saveFavorites(favorites) {
    try {
      localStorage.setItem(FAVORITES_KEY, JSON.stringify(favorites));
    } catch (e) {
      // localStorage unavailable (private browsing, etc.) — favorites just won't persist.
    }
  }

  function isFavorite(id) {
    return loadFavorites().includes(id);
  }

  function toggleFavorite(id) {
    const favorites = loadFavorites();
    const idx = favorites.indexOf(id);
    if (idx === -1) {
      favorites.push(id);
    } else {
      favorites.splice(idx, 1);
    }
    saveFavorites(favorites);
    renderFavoriteButton(id);
    renderFavoritesList();
  }

  function renderFavoriteButton(id) {
    const active = isFavorite(id);
    els.favoriteBtn.setAttribute("aria-pressed", String(active));
    document.getElementById("favorite-icon").textContent = active ? "★" : "☆";
  }

  function renderEntry(entry) {
    if (!entry) {
      els.content.textContent = "Your collection is empty — add some entries to data/collection.js.";
      els.type.textContent = "";
      els.source.textContent = "";
      els.favoriteBtn.style.display = "none";
      return;
    }
    currentEntry = entry;
    els.type.textContent = entry.type;
    els.content.textContent = entry.content;
    els.source.textContent = entry.source;
    renderFavoriteButton(entry.id);
  }

  function renderFavoritesList() {
    const favorites = loadFavorites();
    els.favoritesCount.textContent = String(favorites.length);
    els.favoritesList.innerHTML = "";

    if (favorites.length === 0) {
      const li = document.createElement("li");
      li.className = "favorites-empty";
      li.textContent = "No favorites yet — star an entry to save it here.";
      els.favoritesList.appendChild(li);
      return;
    }

    favorites.forEach((id) => {
      const entry = collection.find((e) => e.id === id);
      if (!entry) return;
      const li = document.createElement("li");

      const textWrap = document.createElement("div");
      textWrap.className = "fav-text";

      const typeEl = document.createElement("span");
      typeEl.className = "fav-type";
      typeEl.textContent = entry.type;

      const contentEl = document.createElement("span");
      contentEl.textContent = entry.content;

      const sourceEl = document.createElement("span");
      sourceEl.className = "fav-source";
      sourceEl.textContent = "— " + entry.source;

      textWrap.appendChild(typeEl);
      textWrap.appendChild(contentEl);
      textWrap.appendChild(sourceEl);

      const removeBtn = document.createElement("button");
      removeBtn.title = "Remove from favorites";
      removeBtn.textContent = "★";
      removeBtn.addEventListener("click", () => {
        toggleFavorite(entry.id);
      });

      li.appendChild(textWrap);
      li.appendChild(removeBtn);
      els.favoritesList.appendChild(li);
    });
  }

  function init() {
    els.date.textContent = new Date().toLocaleDateString(undefined, {
      weekday: "long",
      year: "numeric",
      month: "long",
      day: "numeric"
    });

    renderEntry(getDailyEntry());
    renderFavoritesList();

    els.anotherBtn.addEventListener("click", () => {
      const next = getRandomEntry(currentEntry ? currentEntry.id : null);
      renderEntry(next);
    });

    els.favoriteBtn.addEventListener("click", () => {
      if (currentEntry) toggleFavorite(currentEntry.id);
    });

    els.toggleFavorites.addEventListener("click", () => {
      const hidden = els.favoritesList.hidden;
      els.favoritesList.hidden = !hidden;
      els.favoritesLabel.textContent = hidden ? "Hide favorites" : "Show favorites";
    });
  }

  document.addEventListener("DOMContentLoaded", init);
})();
