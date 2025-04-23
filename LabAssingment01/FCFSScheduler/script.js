
document.addEventListener('DOMContentLoaded', function () {
    // DOM Elements -> access all input and output fields
    const elements = {
        processCountInput: document.getElementById('process-count'),
        generateBtn: document.getElementById('generate-btn'),
        calculateBtn: document.getElementById('calculate-btn'),
        resetBtn: document.getElementById('reset-btn'),
        processInputsContainer: document.getElementById('process-inputs'),
        resultsContainer: document.getElementById('results'),
        processTableBody: document.querySelector('#process-table tbody'),
        ganttChart: document.getElementById('gantt-chart'),
        ganttTimeline: document.getElementById('gantt-timeline'),
        avgWaiting: document.getElementById('avg-waiting'),
        avgTurnaround: document.getElementById('avg-turnaround')
    };

    //Store number of processes
    let nop;

    // Color palette for Gantt chart
    const ganttColors = [
        '#4361ee', '#3f37c9', '#4895ef',
        '#4cc9f0', '#43aa8b', '#f8961e',
        '#f72585', '#7209b7', '#b5179e'
    ];

    // Initialize the application
    function init() {
        setupEventListeners();
        generateProcessInputs();
    }

    // Set up all event listeners
    function setupEventListeners() {
        elements.generateBtn.addEventListener('click', generateProcessInputs); // Generates input fields based on number of processes
        elements.calculateBtn.addEventListener('click', calculateFCFS); // Click to calculate
        elements.resetBtn.addEventListener('click', resetAllFields); // reset input field
    }

    /* *********************** PROCESS INPUT FUNCTIONS *********************** */

    // Generate input fields for processes
    function generateProcessInputs() {
        const processCount = getValidProcessCount();
        elements.processInputsContainer.innerHTML = '';

        for (let i = 0; i < processCount; i++) {
            createProcessInputFields(i);
        }
    }

    // Create input fields for a single process
    function createProcessInputFields(index) {
        const defaultValues = [
            { arrival: 0, burst: 1 }, // Default value set when input field create
        ];

        const defaultValue = defaultValues[index] || { arrival: index, burst: 1 };

        const processGroup = document.createElement('div');
        processGroup.className = 'process-input-group';
        processGroup.innerHTML = `
            <div class="input-group">
                <label class="process-label" for="arrival-${index}">Process ${index + 1} Arrival:</label>
                <input type="number" id="arrival-${index}" min="0" value="${defaultValue.arrival}" required>
            </div>
            <div class="input-group">
                <label class="process-label" for="burst-${index}">Process ${index + 1} Burst:</label>
                <input type="number" id="burst-${index}" min="1" value="${defaultValue.burst}" required>
            </div>
        `;

        elements.processInputsContainer.appendChild(processGroup);
    }

    // Get and validate the number of processes
    function getValidProcessCount() {
        const processCount = parseInt(elements.processCountInput.value);
        nop = processCount;
        return isNaN(processCount) ? 1 : Math.max(1, Math.min(processCount, 100));
    }

    /* ******************************** FCFS CALCULATION FUNCTIONS ******************************** */

    // Main calculation function
    function calculateFCFS() {
        const processCount = getValidProcessCount();
        const processes = collectProcessData(processCount);

        if (!processes) return;

        // Sort by arrival time (FCFS)
        processes.sort((a, b) => a.arrivalTime - b.arrivalTime);

        let currentTime = 0;
        let totalWaiting = 0;
        let totalTurnaround = 0;

        // Calculate metrics for each process
        processes.forEach(process => {
            process.startTime = Math.max(currentTime, process.arrivalTime);
            process.waitingTime = process.startTime - process.arrivalTime;
            process.finishTime = process.startTime + process.burstTime;
            process.turnaroundTime = process.finishTime - process.arrivalTime;

            totalWaiting += process.waitingTime;
            totalTurnaround += process.turnaroundTime;

            currentTime = process.finishTime;
        });

        // Calculate averages
        const avgWT = (totalWaiting / processCount).toFixed(2);
        const avgTAT = (totalTurnaround / processCount).toFixed(2);

        // Display results
        displayResults(processes, avgWT, avgTAT);
    }

    // Collect process data from input fields
    function collectProcessData(processCount) {
        const processes = [];

        for (let i = 0; i < processCount; i++) {
            const arrivalInput = document.getElementById(`arrival-${i}`);
            const burstInput = document.getElementById(`burst-${i}`);

            if (!arrivalInput || !burstInput) {
                alert('Please generate process inputs first');
                return null;
            }

            const arrivalTime = parseInt(arrivalInput.value);
            const burstTime = parseInt(burstInput.value);

            if (isNaN(arrivalTime)) {
                alert(`Invalid arrival time for Process ${i + 1}`);
                arrivalInput.focus();
                return null;
            }

            if (isNaN(burstTime)) {
                alert(`Invalid burst time for Process ${i + 1}`);
                burstInput.focus();
                return null;
            }

            processes.push({
                id: i + 1,
                arrivalTime: arrivalTime,
                burstTime: burstTime
            });
        }

        return processes;
    }

    /* **************************** DISPLAY FUNCTIONS **************************** */

    // Display all results
    function displayResults(processes, avgWT, avgTAT) {
        displayGanttChart(processes);
        displayProcessTable(processes);
        displayAverages(avgWT, avgTAT);
        elements.resultsContainer.classList.remove('hidden');
    }

    // Display the Gantt chart with timeline
    function displayGanttChart(processes) {
        elements.ganttChart.innerHTML = '';
        elements.ganttTimeline.innerHTML = '';

        let currentTime = 0;
        let maxTime = 0;
        var timeDuration = 0;

        // Create Gantt blocks
        processes.forEach((process, index) => {
            // Add idle time if needed
            if (process.startTime > currentTime) {
                createGanttBlock('Idle', process.startTime - currentTime, 'var(--idle-color)', currentTime);
                currentTime = process.startTime;
            }

            // Add process block
            const color = ganttColors[(process.id - 1) % ganttColors.length];
            createGanttBlock(`P${process.id}`, process.burstTime, color, process.finishTime);

            currentTime = process.finishTime;
            maxTime = currentTime;
            timeDuration = process.burstTime;
        });
        // Create timeline markers
        createTimelineMarkers(maxTime, nop, timeDuration);
    }

    // Create a single Gantt block
    function createGanttBlock(text, duration, color, endTime) {
        const block = document.createElement('div');
        block.className = 'gantt-block';
        block.style.flex = duration;
        block.style.backgroundColor = color;
        block.textContent = text;

        // Add end time marker
        const timeMarker = document.createElement('div');
        timeMarker.className = 'gantt-time-marker';
        timeMarker.textContent = endTime;
        timeMarker.style.left = '100%';

        block.appendChild(timeMarker);
        elements.ganttChart.appendChild(block);
    }

    // Create timeline markers for the Gantt chart
    function createTimelineMarkers(maxTime, nop, timeDuration) {
        const steps = Math.min(maxTime, 10);
        const stepSize = maxTime / steps;

        for (let i = 0; i <= steps; i++) {
            const time = Math.round(i * stepSize);
            const marker = document.createElement('span');
            // marker.style.flex = timeDuration;
            marker.textContent = time;
            elements.ganttTimeline.appendChild(marker);
        }
    }

    // Display process table
    function displayProcessTable(processes) {
        elements.processTableBody.innerHTML = '';

        processes.forEach(process => {
            const row = document.createElement('tr');
            row.innerHTML = `
                <td>P${process.id}</td>
                <td>${process.arrivalTime}</td>
                <td>${process.burstTime}</td>
                <td>${process.waitingTime}</td>
                <td>${process.turnaroundTime}</td>
            `;
            elements.processTableBody.appendChild(row);
        });
    }

    // Display average times
    function displayAverages(avgWT, avgTAT) {
        elements.avgWaiting.textContent = avgWT;
        elements.avgTurnaround.textContent = avgTAT;
    }

    /************************* UTILITY FUNCTIONS ************************ */

    // Reset all fields
    function resetAllFields() {
        elements.processCountInput.value = '3';
        elements.processInputsContainer.innerHTML = '';
        elements.resultsContainer.classList.add('hidden');
        generateProcessInputs();
    }

    // Initialize the application
    init();
});