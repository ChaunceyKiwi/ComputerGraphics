function fds(address,option)

%% read file
smf_file = address;
fid = fopen(smf_file, 'r');
if fid == -1
    disp('ERROR: could not open file');
    return;
end
vnum = 1;
fnum = 1;
while (feof(fid) ~= 1)
    line = '';
    line = fgetl(fid);
    if length(line) > 0 & line(1) == 'v'
        dummy = sscanf(line, '%c %f %f %f');
        X(vnum, :) = dummy(2:4, :)';
        vnum = vnum + 1;
    elseif length(line) > 0 & (line(1) == 'f' | line(1) == 't')
        dummy = sscanf(line, '%c %f %f %f');
        F(fnum, :) = dummy(2:4, :)';
        fnum = fnum + 1;
    end
end
fclose(fid);

%% Spectral mesh compression using "Fourier descriptors"
    numOfVert = size(X,1);
    numOfFace = size(F,1);
    K = zeros(numOfVert);
    X_a = zeros(numOfVert,3);
    X_back = zeros(numOfVert,3);

    for i = 1:numOfFace
        index = F(i,:);
        % get K Laplacian operator
        if(K(index(1),index(3)) ~= -1)
           K(index(1),index(1)) = K(index(1),index(1)) + 1;
           K(index(3),index(3)) = K(index(3),index(3)) + 1;
           K(index(1),index(3)) = -1;
           K(index(3),index(1)) = -1;
        end

        if(K(index(1),index(2)) ~= -1)
           K(index(1),index(1)) = K(index(1),index(1)) + 1;
           K(index(2),index(2)) = K(index(2),index(2)) + 1;
           K(index(1),index(2)) = -1;
           K(index(2),index(1)) = -1;
        end

        if(K(index(2),index(3)) ~= -1)
           K(index(2),index(2)) = K(index(2),index(2)) + 1;
           K(index(3),index(3)) = K(index(3),index(3)) + 1;
           K(index(2),index(3)) = -1;
           K(index(3),index(2)) = -1;
        end  
    end
    
    % calcuate eigenvectors
    [V,~] = eig(K);
    Vt = V';
    
    subplot(2,2,1)
    trimesh(F, X(:,1), X(:,2), X(:,3), 'EdgeColor', [0.3 0.3 0.3], ...
        'FaceColor', [0.8 0.8 0.8], 'FaceLighting', 'phong');
        
for loop = 1:size(option,2)
    % Fourier Transform (choose number of descriptor here)
    for i = 1: option(loop)
        X_a(i,:) = Vt(i,:) * X;
    end
    
    % Inversed Fourier Transform
    for i = 1: numOfVert
        X_back(i,:) = V(i,:) * X_a;
    end
    
    subplot(2,2,loop+1)
    trimesh(F, X_back(:,1), X_back(:,2), X_back(:,3), 'EdgeColor', [0.3 0.3 0.3], ...
        'FaceColor', [0.8 0.8 0.8], 'FaceLighting', 'phong');
end