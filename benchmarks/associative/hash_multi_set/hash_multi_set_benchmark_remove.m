% Dataset of unordered_multiset
x1 = [1, 10, 100, 1000, 10000, 100000];
y1 = [23.67, 28.33, 274.33, 2155.33, 22609.33, 244564.67];

% Dataset of hash_multi_set
x2 = [1, 10, 100, 1000, 10000, 100000];
y2 = [75.67, 189.33, 3489.67, 74664, 3665868, 720109811];

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
c_linear = 2;
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
title('Benchmark Comparison: unordered\_multiset vs hash\_multiset (remove)', 'FontSize', 16, 'FontWeight', 'bold');

% Add legend
% 'O(1)', 'O(log n)',
legend('unordered\_multiset', 'hash\_multiset', 'O(n)', 'O(n²)', 'Location', 'northwest');

% Customize the appearance
set(gca, 'FontSize', 12);
set(gca, 'XTickLabel', {'1', '10', '100', '1K', '10K', '100K'});

% Adjust y-axis limits to better visualize the data
ylim([10, 5000000000]);