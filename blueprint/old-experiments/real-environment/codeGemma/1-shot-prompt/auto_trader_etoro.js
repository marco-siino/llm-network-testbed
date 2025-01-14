javascript:(function() {
    function startMonitoring() {
        const closeElementSelector = 'et-select-body-option[automation-id="group-actions-option-instrument-close-trade"]',
            closeAllButtonSelector = 'button[data-etoro-automation-id="close-all-positions-closs-all-button"]',
            totalProfitValueSelector = 'span[data-etoro-automation-id="close-all-positions-details-total-profit-value"]',
            totalEquityValueSelector = 'div[data-etoro-automation-id="close-all-positions-details-total-equity-value"]',
            searchInputSelector = 'input#etoro-search-autocomplete-input',
            amountInputSelector = 'input[automation-id="open-position-amount-input-amount"]',
            acquistaButtonSelector = 'button[automation-id="open-position-by-value-submit-button"]',
            clearButtonSelector = 'button.aa-ClearButton.et-aa-clear-button',
            darkOverlaySelector = '.dark-overlay',
            assetAmountSelector = 'span[automation-id="cd-portfolio-group-list-header-assets-amount"]';

        let isClicking = false,
            observers = [],
            preOrderAssetsNr = 0;

        function getPreOrderAssets() {
            const assetAmountElement = document.querySelector(assetAmountSelector);
            if (assetAmountElement) {
                preOrderAssetsNr = parseInt(assetAmountElement.textContent.replace(/[^\d]/g, '').trim(), 10);
                console.log('Pre-order assets number:', preOrderAssetsNr);
            } else {
                console.error('Asset amount element not found');
            }
        }

        async function fetchTopStock() {
            try {
                const response = await fetch('https://www.beatlespack.eu/trading/get_top_stock.php');
                const data = await response.json();
                return data.symbol || 'BTC';
            } catch (e) {
                console.error('Error fetching top stock:', e);
                return 'BTC';
            }
        }

        function verifyAssetsChange() {
            setTimeout(() => {
                const currentAssetAmountElement = document.querySelector(assetAmountSelector);
                if (currentAssetAmountElement) {
                    const currentAssetsNr = parseInt(currentAssetAmountElement.textContent.replace(/[^\d]/g, '').trim(), 10);
                    console.log('Current assets number:', currentAssetsNr);
                    fetch('https://www.beatlespack.eu/trading/delete_top_stock.php', { method: 'GET' })
                        .then(response => response.json())
                        .then(data => console.log('PHP response:', data))
                        .catch(err => console.error('Error calling PHP script:', err));

                    if (currentAssetsNr == preOrderAssetsNr) {
                        console.log('Assets number not changed, restart with another buying...');
                        setTimeout(() => fetchTopStock().then(topStock => {
                            getPreOrderAssets();
                            typeInSearchInput(topStock);
                            setTimeout(() => attemptToClickInvestButton(toBeReinvested), 20000);
                        }), 20000);
                    } else {
                        console.log('No change in asset number');
                    }
                } else {
                    console.error('Asset amount element not found after purchase');
                }
            }, 20000);
        }

        function observeAllRows() {
            const rows = document.querySelectorAll('div.et-table-row');
            if (rows.length === 0) {
                console.error("No rows found");
                return;
            }

            rows.forEach(row => {
                const targetSpan = row.querySelector('span[automation-id="portfolio-overview-table-body-cell-gain"]');
                if (targetSpan) {
                    const observer = new MutationObserver(function(mutations) {
                        mutations.forEach(function(mutation) {
                            if (mutation.type === 'childList' || mutation.type === 'characterData') {
                                const spanValue = parseFloat(mutation.target.textContent.replace(/[$,]/g, ""));
                                console.log("Detected change in span value:", mutation.target.textContent);

                                if (spanValue > -3.20 && !isClicking) {
                                    isClicking = true;
                                    disconnectObservers();
                                    const dropdownElement = row.querySelector('div[automation-id="group-actions-dropdown-3dots"]');
                                    if (dropdownElement) {
                                        dropdownElement.click();
                                        console.log("Dropdown clicked");
                                        observer.disconnect();
                                        setTimeout(checkForCloseElement, 20000);
                                    } else {
                                        console.error("Dropdown element not found");
                                    }
                                }
                            }
                        });
                    });
                    observer.observe(targetSpan, { childList: true, characterData: true, subtree: true });
                    observers.push(observer);
                } else {
                    console.error("Target span not found in a row");
                }
            });
        }

        function disconnectObservers() {
            observers.forEach(observer => observer.disconnect());
            observers = [];
            console.log("Disconnected all observers");
        }

        function checkForCloseElement(attempts = 10) {
            if (attempts <= 0) {
                console.error('"Chiudi" option not found after several attempts');
                isClicking = false;
                observeAllRows();
                return;
            }
            const closeElement = document.querySelector(closeElementSelector);
            if (closeElement) {
                closeElement.click();
                console.log('"Chiudi" option clicked');
                setTimeout(checkForCloseAllButton, 20000);
            } else {
                console.log('"Chiudi" option not found, trying again...');
                setTimeout(() => checkForCloseElement(attempts - 1), 500);
            }
        }

        function checkForCloseAllButton(attempts = 10) {
            if (attempts <= 0) {
                console.error('"Chiudi Tutto" button not found after several attempts');
                isClicking = false;
                observeAllRows();
                return;
            }
            const closeAllButton = document.querySelector(closeAllButtonSelector);
            if (closeAllButton) {
                const totalProfitValueElement = document.querySelector(totalProfitValueSelector),
                    totalEquityValueElement = document.querySelector(totalEquityValueSelector);
                if (totalProfitValueElement && totalEquityValueElement) {
                    const totalProfit = parseFloat(totalProfitValueElement.textContent.replace(/[$,]/g, "")),
                        totalEquity = parseFloat(totalEquityValueElement.textContent.replace(/[$,]/g, ""));
                    const toBeReinvested = totalEquity - (totalProfit / 2);
                    console.log("Total to be reinvested: $" + toBeReinvested.toFixed(2));
                    closeAllButton.click();
                    console.log('"Chiudi Tutto" button clicked');
                    isClicking = false;
                    setTimeout(() => fetchTopStock().then(topStock => {
                        getPreOrderAssets();
                        typeInSearchInput(topStock);
                        setTimeout(() => attemptToClickInvestButton(toBeReinvested), 20000);
                    }), 20000);
                } else {
                    console.error("Total profit or equity element not found");
                }
            } else {
                console.log('"Chiudi Tutto" button not found, trying again...');
                setTimeout(() => checkForCloseAllButton(attempts - 1), 500);
            }
        }

        function typeInSearchInput(text) {
            const searchInput = document.querySelector(searchInputSelector);
            if (searchInput) {
                searchInput.focus();
                searchInput.value = text;
                const inputEvent = new Event('input', { bubbles: true });
                searchInput.dispatchEvent(inputEvent);
                console.log(`Typed "${text}" into the search input`);
            } else {
                console.error("Search input not found");
            }
        }

        function attemptToClickInvestButton(toBeReinvested, attempts = 10) {
            if (attempts <= 0) {
                console.error('"Invest" button not found after several attempts');
                return;
            }
            const investButton = document.querySelector('button[automation-id="btn-trade-item-from-search"]');
            if (investButton) {
                investButton.click();
                console.log('"Invest" button clicked');
                setTimeout(() => attemptToTypeInAmount(toBeReinvested), 20000);
            } else {
                console.log('"Invest" button not found, trying again...');
                setTimeout(() => attemptToClickInvestButton(toBeReinvested, attempts - 1), 500);
            }
        }

        function attemptToTypeInAmount(toBeReinvested, attempts = 10) {
            if (attempts <= 0) {
                console.error('"Amount" input not found after several attempts');
                return;
            }
            const amountInput = document.querySelector(amountInputSelector);
            if (amountInput) {
                amountInput.focus();
                amountInput.value = toBeReinvested.toFixed(2);
                const inputEvent = new Event('input', { bubbles: true });
                amountInput.dispatchEvent(inputEvent);
                console.log(`Entered amount: $${toBeReinvested.toFixed(2)}`);
                setTimeout(clickAcquistaButton, 20000);
            } else {
                console.log('"Amount" input not found, trying again...');
                setTimeout(() => attemptToTypeInAmount(toBeReinvested, attempts - 1), 500);
            }
        }

        function clickAcquistaButton() {
            const acquistaButton = document.querySelector(acquistaButtonSelector);
            if (acquistaButton) {
                acquistaButton.click();
                console.log('"Acquista" button clicked');
                setTimeout(() => {
                    clearSearchAndRestart();
                    closeSearchBar();
                    verifyAssetsChange();
                }, 20000);
            } else {
                console.error('"Acquista" button not found');
            }
        }

        function clearSearchAndRestart() {
            const clearButton = document.querySelector(clearButtonSelector);
            if (clearButton) {
                clearButton.click();
                console.log('Search input cleared');
                clickOutsideToCloseSuggestions();
                removeDarkOverlay();
                setTimeout(observeAllRows, 20000);
            } else {
                console.error('"Clear" button not found');
                setTimeout(observeAllRows, 20000);
            }
        }

        function closeSearchBar() {
            const searchPanel = document.querySelector('div.aa-PanelLayout.aa-Panel--scrollable');
            if (searchPanel) {
                searchPanel.style.display = 'none';
                console.log('Search panel closed');
            } else {
                console.error('Search panel not found');
            }
        }

        function clickOutsideToCloseSuggestions() {
            document.body.click();
            console.log("Clicked outside to close suggestions");
        }

        function removeDarkOverlay() {
            const darkOverlay = document.querySelector(darkOverlaySelector);
            if (darkOverlay) {
                darkOverlay.remove();
                console.log("Removed dark overlay");
            }
        }

        getPreOrderAssets();
        observeAllRows();
    }

    startMonitoring();
})();
