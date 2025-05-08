% Dataset of unordered_map
x1 = [1, 10, 100, 1000, 10000, 100000];
y1 = [27.67, 28, 232.67, 2161.33, 23795, 214035.33];

% Dataset of hash_map
x2 = [1, 10, 100, 1000, 10000, 100000];
y2 = [75.67, 112.33, 2497, 71214.67, 3581035, 750094015.7];

% Create a new figure with a specific size
figure('Position', [100, 100, 800, 600]);

loglog(x1, y1, 'b-o', 'LineWidth', 2, 'MarkerSize', 8, 'MarkerFaceColor', 'b');
hold on;
loglog(x2, y2, 'r-s', 'LineWidth', 2, 'MarkerSize', 8, 'MarkerFaceColor', 'r');

% Generate reference lines for different complexity classes
x_ref = logspace(0, 5, 100); % Generate 100 points from 10^0 to 10^5

% Scale factors to position the reference lines appropriately
% c_const = 100;
% c_log = 20;
c_linear = 1;
c_quadratic = 0.05;

% O(1) - Constant time
% y_const = c_const * ones(size(x_ref));
% loglog(x_ref, y_const, '--', 'Color', [0.5, 0.5, 0.5], 'LineWidth', 1.5);

% O(log n) - Logarithmic time
% y_log = c_log * log10(x_ref);
% loglog(x_ref, y_log, '-.', 'Color', [0.0, 0.7, 0.0], 'LineWidth', 1.5);

% O(n) - Linear time
y_linear = c_linear * x_ref;
loglog(x_ref, y_linear, ':', 'MarkerFaceColor', 'r', 'LineWidth', 1.5);

% O(n^2) - Quadratic time
y_quadratic = c_quadratic * x_ref.^2;
loglog(x_ref, y_quadratic, ':', 'MarkerFaceColor', 'b', 'LineWidth', 2);

% Add grid lines
grid on;

% Add labels and title
xlabel('Input Size', 'FontSize', 14, 'FontWeight', 'bold');
ylabel('Execution Time (µs)', 'FontSize', 14, 'FontWeight', 'bold');
title('Benchmark Comparison: unordered\_map vs hash\_map (find)', 'FontSize', 16, 'FontWeight', 'bold');

% Add legend
% 'O(1)', 'O(log n)',
legend('unordered\_map', 'hash\_map', 'O(n)', 'O(n²)', 'Location', 'northwest');

% Customize the appearance
set(gca, 'FontSize', 12);
set(gca, 'XTickLabel', {'1', '10', '100', '1K', '10K', '100K'});

% Adjust y-axis limits to better visualize the data
ylim([10, 8000000000]);