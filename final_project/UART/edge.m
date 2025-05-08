clc;
clear;
close all;

% Load original image
fid1 = fopen('image.raw', 'rb');
orig = fread(fid1, [64, 64], 'uint8');
fclose(fid1);

% Load edge-detected image
fid2 = fopen('teraterm.bin', 'rb');
edge1 = fread(fid2, [64, 64], 'uint8');
fclose(fid2);

% Transpose for correct orientation
orig = orig';
edge2 = edge1';

% Show both images in one figure using subplot
figure;
subplot(1,2,1);
imshow(orig, []);
title('Original Image');

subplot(1,2,2);
imshow(edge2, []);
title('Edge-Detected Image');
