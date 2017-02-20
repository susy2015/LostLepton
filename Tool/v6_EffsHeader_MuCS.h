  double ttbar_mtwcorrfactor[7] = {1.04399,1.06604,1.07511,1.09477,1.11818,1.19641,1.63419};
  double ttbar_mus_acc[84] = {0.782078,0.832794,0.84547,0.891908,0.912939,0.77848,0.781545,0.859236,0.853415,0.840614,0.806399,0.800198,0.848331,0.938134,0.911118,0.847717,0.840538,0.860095, 0.90763028249,0.844725,0.894372,0.799611,0.835843,0.842955,0.803319,0.866169,0.803749,0.703399,0.825038,0.786609,0.807629,0.828738,0.882303,0.911172, 0.90749046468,0.9632, 0.9744523306,0.781471,0.754061,0.725711,0.94071,0.874611,0.860046,0.85388,0.772502,0.915475,0.84176,0.939116,0.918657,0.948766,0.944007,0.945897,0.808416,0.860068,0.895743,0.910783,0.795116,0.846736,0.905423,0.919898,0.941753,0.958494,0.80175,0.852255,0.933809,0.795406,0.833465,0.847783,0.969876,0.830997,0.887594,0.862694,0.987645,0.88935,0.898245,0.893793,0.941655, 0.9155022718,0.915693,0.958764,0.973681, 0.92149065541,0.97155,0.977083};
  double ttbar_mus_recoeff[7][5] = {{0.968488,0.96422,0.963827,0.949228,0.927524},{0.971584,0.976348,0.97564,0.977992,0.955123},{0.976658,0.978893,0.972775,0.97662,0.961779},{0.97899,0.977161,0.976627,0.969797,0.964318},{0.982553,0.980337,0.976478,0.966717,0.946078},{0.977556,0.979114,0.971473,0.951352,0.963094},{0.890963,0.909389,0.92556,0.908311,0.940944}};
  double ttbar_mus_isoeff[7][5] = {{0.964534,0.954573,0.933517,0.838089,0.493915},{0.980143,0.968581,0.955815,0.872807,0.567898},{0.987297,0.983426,0.975679,0.890237,0.667139},{0.985743,0.983094,0.977894,0.877268,0.681197},{0.995458,0.994217,0.988304,0.902521,0.750542},{0.997558,0.996194,0.994897,0.962024,0.869259},{0.997064,0.998968,0.998401,0.987629,0.935372}};
  double ttbar_els_acc[84] = {0.796645,0.826848,0.846874,0.854893,0.845223,0.79733,0.779059,0.800175,0.898012,0.842711,0.785149,0.777837,0.807476,0.941625,0.912233,0.880172,0.817731,0.885087, 0.93711782822, 0.80373392314,0.892648,0.796412,0.806848,0.875736,0.774997,0.864047,0.80618,0.802467,0.868117,0.918219,0.898213,0.902169,0.912748,0.839107, 0.87184631511, 0.80589664987, 0.85004794433,0.755983,0.803199,0.831157,0.699148,0.85657,0.8372,0.812487,0.807285,0.859322,0.898584,0.873767,0.884628,0.904158,0.895756,0.882666,0.789989,0.780784,0.886407,0.833375,0.85099,0.827151,0.906764,0.880177,0.911781,0.957564,0.813453,0.849991,0.849762,0.799984,0.771181, 0.83072696694,0.951567,0.809553,0.855539,0.718188,0.939812,0.848473,0.962864,0.922024,0.905066, 0.89868092018,0.915945,0.8699,0.920726,0.889512,0.857331, 0.85052562121};
  double ttbar_els_recoeff[7][5] = {{0.758105,0.708367,0.71503,0.656886,0.546074},{0.841182,0.82355,0.836309,0.802026,0.705133},{0.895998,0.877852,0.857122,0.827865,0.777098},{0.902172,0.879773,0.869395,0.837012,0.809746},{0.895065,0.881069,0.881845,0.823637,0.725212},{0.894334,0.886997,0.870623,0.863653,0.681066},{0.871983,0.845043,0.815716,0.8359,0.775167}};
  double ttbar_els_isoeff[7][5] = {{0.873757,0.863325,0.834469,0.721771,0.334209},{0.929712,0.915527,0.890873,0.762907,0.399165},{0.967022,0.950797,0.92085,0.806349,0.465272},{0.963684,0.959405,0.935226,0.773053,0.513018},{0.985612,0.973892,0.963919,0.844062,0.71972},{0.98962,0.987442,0.975211,0.935354,0.889453},{0.994913,0.989664,0.986605,0.950629,0.963934}};
  double ttbar_corrfactor_di_mus = 0.994044;
  double ttbar_corrfactor_di_els = 0.971781;
  double isoTrackEff_SB[84] = {0.590493, 0.561236, 0.695239, 0.644243, 0.456505, 0.589549, 0.590079, 0.605812, 0.640944, 0.567335, 0.620706, 0.553416, 0.590924, 0.51710838398, 0.457827, 0.639981, 0.601433, 0.62489752222, 0.72177411931, 0.79832086394, 0.71752553929, 0.575559, 0.575305, 0.637019, 0.639435, 0.656953, 0.569597, 0.624, 0.522413, 0.801731, 0.635865, 0.53689, 0.456575, 0.478029, 0.718798, 0.73107753131, 0.83786506351, 0.583126, 0.587228, 0.619752, 0.640475, 0.593927, 0.621907, 0.661975, 0.542692, 0.665093, 0.619586, 0.70250636576, 0.540293, 0.524838, 0.721528, 0.60217939892, 0.616599, 0.612173, 0.63301, 0.687242, 0.630832, 0.53934120243, 0.499387, 0.534385, 0.63721, 0.68155, 0.593246, 0.602999, 0.703103, 0.630304, 0.506049, 0.6319719927, 0.698086, 0.772164, 0.518214, 0.539126, 0.80099439149, 0.676463, 0.5882, 0.588093, 0.575513, 0.62543571685, 0.556933, 0.61200427902, 0.554402, 0.46151873975, 0.51445531834, 0.51129047553};
