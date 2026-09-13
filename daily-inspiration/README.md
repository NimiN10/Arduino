# Daily Inspiration

A small personal app that surfaces one meaningful thing from your own
collection each day — a quote, a memory, a goal, or an idea — with a
"show me another" button and a way to mark favorites.

## Running it

No build step or server required. Just open `index.html` in a browser.

If your browser blocks local scripts from `file://` pages, serve the folder
instead:

```bash
cd daily-inspiration
python3 -m http.server 8000
```

Then visit `http://localhost:8000`.

## Adding your own notes

Edit `data/collection.js`. Each entry looks like:

```js
{
  id: "unique-id",
  type: "quote",       // "quote" | "memory" | "goal" | "idea" | "journal"
  content: "The text itself.",
  source: "Where it's from",
  dateAdded: "2024-01-01"
}
```

Add as many as you like — the app picks one deterministically for "today"
(so it stays the same all day and changes tomorrow), and "Show me another"
picks a random different one from the whole collection.

## Favorites

Favorites are saved in your browser's `localStorage`, so they persist
between visits on the same device/browser but aren't synced anywhere.
