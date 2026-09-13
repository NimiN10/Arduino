/**
 * Your personal collection.
 *
 * Add, edit, or remove entries freely — this is your notebook.
 * Each entry needs:
 *   id       - unique string (anything, just don't repeat it)
 *   type     - "quote" | "memory" | "goal" | "idea" | "journal"
 *   content  - the text itself
 *   source   - where it's from (a person, a date, "me", a project name, etc.)
 *   dateAdded - "YYYY-MM-DD", used only for sorting/reference
 *
 * Optional:
 *   tags - array of strings, for your own organization (not used by the app yet)
 */

const INSPIRATION_COLLECTION = [
  {
    id: "q-marcus-1",
    type: "quote",
    content: "You have power over your mind — not outside events. Realize this, and you will find strength.",
    source: "Marcus Aurelius, Meditations",
    dateAdded: "2024-01-05"
  },
  {
    id: "q-rilke-1",
    type: "quote",
    content: "Be patient toward all that is unsolved in your heart and try to love the questions themselves.",
    source: "Rainer Maria Rilke",
    dateAdded: "2024-02-11"
  },
  {
    id: "idea-side-project",
    type: "idea",
    content: "Build a small Arduino weather station that logs to a spreadsheet automatically — combine the water sensor project with a temperature/humidity sensor and a simple dashboard.",
    source: "Idea backlog",
    dateAdded: "2024-03-02"
  },
  {
    id: "memory-summer-trip",
    type: "memory",
    content: "The night we stayed up on the roof watching the meteor shower and lost track of time talking about nothing and everything. Nobody checked their phone once.",
    source: "Summer, a few years back",
    dateAdded: "2024-03-20"
  },
  {
    id: "goal-learn-embedded",
    type: "goal",
    content: "Get comfortable enough with embedded C and microcontroller programming that I can prototype a hardware idea in a weekend without looking everything up.",
    source: "2024 goals",
    dateAdded: "2024-01-01"
  },
  {
    id: "journal-quiet-morning",
    type: "journal",
    content: "Woke up early without an alarm today. Made coffee slowly, sat by the window. It's strange how much calmer everything feels when I'm not rushing into the day.",
    source: "Journal entry",
    dateAdded: "2024-04-14"
  },
  {
    id: "q-feynman-1",
    type: "quote",
    content: "I would rather have questions that can't be answered than answers that can't be questioned.",
    source: "Richard Feynman",
    dateAdded: "2024-02-28"
  },
  {
    id: "idea-teach-someone",
    type: "idea",
    content: "Teach a friend the basics of soldering and let them build something small and useless just for the joy of making it work.",
    source: "Idea backlog",
    dateAdded: "2024-05-03"
  },
  {
    id: "memory-first-project",
    type: "memory",
    content: "The first time the Snake game actually ran on the board and didn't crash. Genuinely felt like magic, even though I'd written every line of it.",
    source: "Notes on Snake project",
    dateAdded: "2024-01-20"
  },
  {
    id: "goal-write-more",
    type: "goal",
    content: "Write something — anything — every day, even if it's three sentences. The goal isn't quality, it's not losing the thread.",
    source: "2024 goals",
    dateAdded: "2024-01-01"
  },
  {
    id: "q-thoreau-1",
    type: "quote",
    content: "Go confidently in the direction of your dreams. Live the life you have imagined.",
    source: "Henry David Thoreau",
    dateAdded: "2024-03-15"
  },
  {
    id: "journal-hard-day",
    type: "journal",
    content: "Rough day, but I noticed I handled it better than I would have a year ago. Small progress is still progress.",
    source: "Journal entry",
    dateAdded: "2024-05-22"
  },
  {
    id: "idea-notes-app",
    type: "idea",
    content: "A tiny app that resurfaces one old note a day so nothing good gets buried and forgotten in a folder somewhere.",
    source: "Idea backlog",
    dateAdded: "2024-06-01"
  },
  {
    id: "q-annefrank-1",
    type: "quote",
    content: "How wonderful it is that nobody need wait a single moment before starting to improve the world.",
    source: "Anne Frank",
    dateAdded: "2024-04-02"
  },
  {
    id: "memory-grandparent",
    type: "memory",
    content: "Sitting in the kitchen listening to stories about a life so different from mine, and realizing how little I'd actually asked before.",
    source: "Family memory",
    dateAdded: "2024-02-14"
  }
];
