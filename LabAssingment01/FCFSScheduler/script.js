document.addEventListener('DOMContentLoaded', () => {
    // Accessing key DOM elements once for reusability
    const el = {
        processCountInput: document.getElementById('process-count'),
        generateBtn: document.getElementById('generate-btn'),
        calculateBtn: document.getElementById('calculate-btn'),
        resetBtn: document.getElementById('reset-btn'),
        inputsContainer: document.getElementById('process-inputs'),
        resultsContainer: document.getElementById('results'),
        tableBody: document.querySelector('#process-table tbody'),
        ganttChart: document.getElementById('gantt-chart'),
        ganttTimeline: document.getElementById('gantt-timeline'),
        avgWaiting: document.getElementById('avg-waiting'),
        avgTurnaround: document.getElementById('avg-turnaround')
    };

    let nop; // number of processes
    const colors = ['#4361ee', '#3f37c9', '#4895ef', '#4cc9f0', '#43aa8b', '#f8961e', '#f72585', '#7209b7', '#b5179e'];

    // Setup event listeners
    function setup() {
        el.generateBtn.onclick = generateInputs;
        el.calculateBtn.onclick = calculateFCFS;
        el.resetBtn.onclick = reset;
        generateInputs(); // generate default inputs on load
    }

    // Generate dynamic input fields
    function generateInputs() {
        const count = getValidProcessCount();
        el.inputsContainer.innerHTML = '';
        for (let i = 0; i < count; i++) {
            const arrival = i, burst = 1;
            el.inputsContainer.innerHTML += `
                <div class="process-input-group">
                    <div class="input-group">
                        <label class="process-label" for="arrival-${i}">Process ${i + 1} Arrival:</label>
                        <input type="number" id="arrival-${i}" min="0" value="${arrival}" required>
                    </div>
                    <div class="input-group">
                        <label class="process-label" for="burst-${i}">Process ${i + 1} Burst:</label>
                        <input type="number" id="burst-${i}" min="1" value="${burst}" required>
                    </div>
                </div>`;
        }
    }

    // Validate process count between 1 and 100
    function getValidProcessCount() {
        const count = parseInt(el.processCountInput.value);
        nop = count;
        return isNaN(count) ? 1 : Math.max(1, Math.min(count, 100));
    }

    // Perform FCFS calculation
    function calculateFCFS() {
        const count = getValidProcessCount();
        const processes = [];

        // Gather input values for arrival and burst times
        for (let i = 0; i < count; i++) {
            const arrival = parseInt(document.getElementById(`arrival-${i}`)?.value);
            const burst = parseInt(document.getElementById(`burst-${i}`)?.value);

            if (isNaN(arrival) || isNaN(burst)) {
                alert(`Invalid input for Process ${i + 1}`);
                return;
            }

            processes.push({ id: i + 1, arrivalTime: arrival, burstTime: burst });
        }

        // Sort by arrival time for FCFS
        processes.sort((a, b) => a.arrivalTime - b.arrivalTime);

        let time = 0, totalWT = 0, totalTAT = 0;

        processes.forEach(p => {
            p.startTime = Math.max(time, p.arrivalTime); // CPU waits if process hasn't arrived
            p.waitingTime = p.startTime - p.arrivalTime;
            p.finishTime = p.startTime + p.burstTime;
            p.turnaroundTime = p.finishTime - p.arrivalTime;
            time = p.finishTime;

            totalWT += p.waitingTime;
            totalTAT += p.turnaroundTime;
        });

        const avgWT = (totalWT / count).toFixed(2);
        const avgTAT = (totalTAT / count).toFixed(2);

        displayAll(processes, avgWT, avgTAT);
    }

    // Show results (table + Gantt chart + averages)
    function displayAll(processes, avgWT, avgTAT) {
        showTable(processes);
        showGantt(processes);
        el.avgWaiting.textContent = avgWT;
        el.avgTurnaround.textContent = avgTAT;
        el.resultsContainer.classList.remove('hidden');
    }

    // Show process result table
    function showTable(processes) {
        el.tableBody.innerHTML = '';
        processes.forEach(p => {
            el.tableBody.innerHTML += `
                <tr>
                    <td>P${p.id}</td>
                    <td>${p.arrivalTime}</td>
                    <td>${p.burstTime}</td>
                    <td>${p.waitingTime}</td>
                    <td>${p.turnaroundTime}</td>
                </tr>`;
        });
    }

    // Show Gantt chart
    function showGantt(processes) {
        el.ganttChart.innerHTML = '';
        el.ganttTimeline.innerHTML = '';
        let time = 0, maxTime = 0;

        processes.forEach(p => {
            if (p.startTime > time) {
                createBlock('Idle', p.startTime - time, 'var(--idle-color)', p.startTime);
                time = p.startTime;
            }

            const color = colors[(p.id - 1) % colors.length];
            createBlock(`P${p.id}`, p.burstTime, color, p.finishTime);
            time = p.finishTime;
            maxTime = time;
        });

        createTimeline(maxTime);
    }

    // Gantt chart block creation
    function createBlock(label, duration, color, end) {
        const block = document.createElement('div');
        block.className = 'gantt-block';
        block.style.flex = duration;
        block.style.backgroundColor = color;
        block.textContent = label;

        const marker = document.createElement('div');
        marker.className = 'gantt-time-marker';
        marker.textContent = end;
        marker.style.left = '100%'; // right-aligned
        block.appendChild(marker);

        el.ganttChart.appendChild(block);
    }

    // Create evenly spaced time labels in timeline
    function createTimeline(max) {
        const steps = Math.min(max, 10); // limit to 10 labels
        const stepSize = max / steps;

        for (let i = 0; i <= steps; i++) {
            const time = Math.round(i * stepSize);
            const marker = document.createElement('span');
            marker.textContent = time;
            el.ganttTimeline.appendChild(marker);
        }
    }

    // Reset everything
    function reset() {
        el.processCountInput.value = '3';
        el.inputsContainer.innerHTML = '';
        el.resultsContainer.classList.add('hidden');
        generateInputs();
    }

    setup(); // start everything
});
