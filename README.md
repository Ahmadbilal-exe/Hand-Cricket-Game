# 🏏 Hand Cricket Game in C

A feature-rich, interactive **Hand Cricket Game** written in C as a Programming Fundamentals (PF) project. Built with ANSI terminal colors, ASCII box-drawing interfaces, dynamic animations, persistent file storage for match records, and **full cross-platform compatibility for both Linux and Windows**.

---

## 🌟 Features

- **🎮 1 vs 1 Quick Game**: Play a fast-paced head-to-head match against the Computer with custom overs (1–50).
- **👥 11 vs 11 Squid Game**: Full team match! Enter your custom 11-player roster and take on the Computer's hardware-themed lineup (`PROCESSOR`, `CPU`, `RAM`, etc.) with over-by-over bowler rotations and individual batsman tracking.
- **🪙 Animated Coin Toss**: Realistic, animated coin-toss simulation (Heads or Tails) deciding who bats or bowls first.
- **🏆 High Scores & Leaderboards**:
  - Automatically records match outcomes to `1v1game.txt` and `11v11game.txt`.
  - View Top 3 players in 1v1 matches.
  - View Top 3 teams in 11v11 matches ranked by runs and wickets.
- **🎨 Vibrant Terminal UI**: Styled using ANSI color codes, Unicode box frames, ball-by-ball scoreboards, and live target/required-run calculations.
- **💻 Cross-Platform**: Runs seamlessly on both **Windows** (CMD / PowerShell) and **Linux** terminals out of the box.

---

## 📖 Rules of Hand Cricket

1. **Number Selection**: In every delivery, batsman and bowler choose a number between **1 and 6**.
2. **Scoring Runs**: If the batsman and bowler choose different numbers, the batsman scores runs equal to their chosen number.
3. **Wicket (OUT)**: If both the batsman and the bowler choose the exact same number, the batsman is **OUT**!
4. **Innings & Target**:
   - The team batting first sets a target score.
   - The team batting second chases the target within the allotted overs or wickets.

---

## 🛠️ Compilation & Execution

### On Linux

Compile using `gcc`:
```bash
gcc -Wall -Wextra abdulkhalique.c -o hand_cricket
./hand_cricket
```

### On Windows

#### Using MinGW / GCC:
```cmd
gcc abdulkhalique.c -o hand_cricket.exe
hand_cricket.exe
```

#### Using MSVC (Developer Command Prompt):
```cmd
cl abdulkhalique.c /Fe:hand_cricket.exe
hand_cricket.exe
```

> **Note for Windows users**: The game automatically configures console output code page (`CP 65001`) to render UTF-8 box characters and colors properly in Windows CMD and PowerShell.

---

## 📂 Project Structure

```text
├── abdulkhalique.c      # Main cross-platform source code (Linux & Windows)
├── 1v1game.txt          # Persistent match records for 1 vs 1 games
├── 11v11game.txt        # Persistent match records for 11 vs 11 team games
└── README.md            # Project documentation
```

---

## 👤 Author

Developed by **Abdul Khalique**
- First Semester Programming Fundamentals (PF) Project
- Cross-platform C Console Application

