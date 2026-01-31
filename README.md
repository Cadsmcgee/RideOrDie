# Green Team
GAM-305-12908-M01 Digital Game Development

## Module Two Team Project Plan
**Contributors:** Rylan, Zachary, Devin, Travisk, Kenan*

### Team Roles
* **Team Lead:** Rylan
* **Artist:** Kenan
* **Programmer:** Devin / Travis
* **UI/UX Programmer/Designer:** Rylan
* **Level Designer/World Builder:** Zack / Travis

---

### 1. Scenario & Additional Elements
**Scenario:** Third-Person Game (Theme: Vehicle Zombie Survival)

**Rationale:** We are using the Unreal Third-Person template but replacing the character with a car to create a survival driving game.

**The Four Additional Elements:**
* **Vehicle Physics & Combat:** Using the car as a weapon to run over zombies (and taking damage from them).
* **Horde AI Logic:** Simple AI that makes zombies swarm toward the player's position.
* **Resource/Pickup System:** Collecting fuel or repair kits to keep the run going.
* **Win/Loss State UI:** "Car Destroyed" screen (Loss)\ A zombies killed count until all zombies killed or a survival timer (Win)

### 2. Brainstorming on Content (Assets)
We brainstormed the specific assets needed to make that scenario work:
* **Art:** Vehicle model, Zombie character model, City/Highway environment assets (roads, barriers), UI elements (Health bar, Fuel gauge).
* **Audio:** Engine revving, impact sounds (hitting zombies), background ambient track, game over sound effects.
* **Code:** Vehicle controller script, Enemy navigation (NavMesh), Game Loop Manager (Spawn logic, Win/Loss conditions).

### 3. Development Schedule & Timeline
* **Week 2 – Planning & Setup**
  * Finalize game concept and scope (top-down survival)
  * Assign roles and responsibilities
  * Set up repo, engine/project, basic folder structure
  * Draft high-level design document
* **Week 3 – Core Systems (Alpha Start)**
  * Player movement and camera
  * Basic enemy AI and spawning
  * Core combat or interaction mechanic
  * Placeholder UI (health, basic HUD)
* **Week 4 – Alpha Build**
  * Core gameplay loop playable
  * One complete level or area
  * Basic win/lose condition
  * **Alpha Submission**
* **Week 5 – Feature Expansion (Beta Start)**
  * Additional enemies or mechanics
  * Improved UI/UX pass
  * Sound effects and basic music
  * Bug fixes from Alpha feedback
* **Week 6 – Beta Build**
  * Full playable experience end-to-end
  * Balance tuning
  * Visual polish pass
  * **Beta Submission**
* **Week 7 – Final Polish & Submission**
  * Final bug fixes
  * Performance cleanup
  * Final UI/UX tweaks
  * Final build and documentation submission

### 4. Alpha vs. Beta Development Goals

**Alpha Stage (Functionality Focus)**
* **Assets:** Grey-box environment and placeholder models for car and zombies.
* **Functionality:**
  * Car drives without physics errors.
  * Zombies spawn and track the player.
  * Basic collision logic (hitting zombies works).
* **Tracking:** Core mechanics are feature-complete.

**Beta Stage (Polish Focus)**
* **Assets:** Final meshes, textures, and UI art implemented. Audio (SFX/Music) added.
* **Functionality:**
  * Win/Loss screens fully working.
  * Handling tuned for better game feel.
  * Performance optimized.
* **Tracking:** Content lock (no new features), focus on bug fixing.

---

### 5. Communication Method
* **Discord**

### 6. Meeting Plans
* **TBD**

### 7. Task Assignment & Reporting
* **Method:** Google Doc Traceability Matrix

## Module Three Project Log - Team Development: QA and Testing Plan.
**Contributors:** Rylan, Zachary, Devin, Travisk, Kenan*

How we are testing everything Instead of waiting until the end, we are going to test things as we make them. We want to make sure individual parts (like the car physics or a specific zombie) actually work on their own before we try to put them into the main level.

Weekly Schedule

Monday – Thursday (Building): We work on our assigned features and test them on our own computers first to make sure they aren't totally broken.

Friday (Putting it together): Everyone uploads their work to the main project files. We make a "build" of the game so everyone has the same version.

Saturday/Sunday (Test Day): The whole team plays the game together. We look for bugs, see if the game is actually fun, and check if the new stuff works.

The 3 Main Testing Stages

Play Test (Early on): We are testing the "grey-box" version just to see if the movement and zombies feel good. We aren't worried about graphics yet, just gameplay.

Code Release (During development): Every week we check the Friday build against our list to make sure the new code didn't break the old stuff (regression testing).

Demo (Near the end): We will test a polished "Vertical Slice" of the game to make sure it doesn't crash while we are showing it off to people.

Test Item Checklist

Controls

What to look for: Do the keys (WASD) and controller work instantly without lag?

Pass/Fail: [ ]

Logic

What to look for: Does the game actually know when you win or die?

Pass/Fail: [ ]

Game Loop

What to look for: Can you Start -> Play -> Die -> and Restart without it crashing?

Pass/Fail: [ ]

Mechanics

What to look for: Do powerups work? Does the car drive right or does it flip over too much?

Pass/Fail: [ ]

Performance

What to look for: Does the game lag when there are a lot of zombies?

Pass/Fail: [ ]

Tracking Bugs & Changes

Updating the Plan: We have meetings on Wednesdays and Saturdays. If we decide to cut a feature or change how something works (like how fast the car goes), we will update our Traceability Matrix so we don't forget.

Reporting Bugs: When we find bugs during our Saturday playtests, we will write them down in the Matrix. We'll note how bad the bug is and how to make it happen again.

Tracking Fixes: We will use the matrix to see what's still broken. Once a bug is fixed in the next Friday build, we will mark it as "Resolved."



