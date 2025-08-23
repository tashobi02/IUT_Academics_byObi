# CSE 4404: Algorithms Lab

Welcome to the repository for **CSE 4404: Algorithms Lab for the Summer 23–24 semester at the Islamic University of Technology**. This repository will be used throughout the semester for distributing lab tasks, editorials, and evaluating student submissions for **Section 1B**.

---

## 📁 Repository Structure

```
.
├── General Lab Instructions.pdf
├── README.md                         # This file
├── localjudge.sh                     # Bash script for testing submissions locally
├── Lab 1/
│   ├── Lab 1 Handout.pdf
│   ├── Lab 1 Editorial.md            # Editorial (added after deadline)
│   ├── Task A/
│   │   ├── input/                    # Input files (e.g., input0.txt, input1.txt, ...)
│   │   ├── answer/                   # Expected output files (e.g., answer0.txt, answer1.txt, ...)
│   │   ├── submission/               # Submission files in .cpp format
│   │   └── limits.yaml               # Specifies time limit in seconds and memory limit in MB
│   └── Task B/
│       └── ...
├── Lab 2/
│   └── ...
└── ...
```

---

## 🔄 Workflow Overview

### 🟢 Lab Release

At the beginning of each lab, the instructor will push the lab folder to this repository and create a Google Classroom assignment.

Each **Lab** folder contains multiple **Task** folders. Each **Task** folder contains:

- A set of **input/output file pairs** (`input/input0.txt`, `answer/answer0.txt`, etc.)
- A `limits.yaml` file defining the time and memory constraints.
- A `submission/` folder where you need to place your C++ file.

### 📥 Getting the Lab Files

- Clone the repository (first time):
  ```bash
  git clone https://github.com/ir-rafio/iut-algorithms-lab-1b-summer-23-24
  ```
- Or pull the latest changes (if already cloned):
  ```bash
  git pull
  ```

### 🧑‍💻 Solving and Submitting

- Implement your solution(s) in C++.
- Save them using the following naming format: `{full_student_id}_lab{X}_task{Y}.cpp`.
  Example: `190041125_lab1_taskA.cpp`.
- For multiple submissions, use suffixes. Example: `190041125_lab1_taskA_v2.cpp`.
- Upload your `.cpp` file(s) to the corresponding assignment in **Google Classroom**.

> The submission period is usually **1 week**, but always check **Google Classroom** for the exact deadline.

### 🔒 After Deadline

After the submission deadline:

- The instructor will push:
  - The **Lab Editorial** explaining approaches and solutions
  - All students' submissions for that lab
- Students are encouraged to:
  - Read the editorial to understand the correct logic
  - Review classmates' submissions to explore alternative approaches

---

## 🧪 Local Testing

Before submitting, you can test your submissions locally using the script `localjudge.sh`.

### ✅ Requirements

- A Linux environment
- `g++` with C++17 support

### 🚀 First-Time Setup

1. Open a terminal in the base directory of the repository.
2. Give the judge script execute permission:
   ```bash
   chmod +x localjudge.sh
   ```

### 🧪 Usage (Per Task)

Run the judge with the path to the task folder:

```bash
./localjudge.sh -path "./Lab {lab_id}/Task {task_id}"
```

Example:

```bash
./localjudge.sh -path "./Lab 1/Task A"
```

This will:

- Compile each `.cpp` file in the `submission/` folder
- Run the program against all test cases
- Display verdict.

---

## 📌 Notes

- Don’t change or delete any files except your submissions.
- You **do not** have write access to the repository — your changes remain local.
- All evaluations are case-sensitive, and for floating-point numbers, the precision needs to be matched exactly as instructed.
